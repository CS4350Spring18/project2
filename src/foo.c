#include <stdio.h>
#include <stdlib.h>

#include "editing.h"
#include "load_file.h"
#include "save_file.h"
#include "page_struct.h"
#include "page_ops.h"
#include "find.h"
#include "newline.h"
#include "deleteline.h"

static int row;
static int col;
static char* fileName;

void initView(Page* page);

static int driver(int ch, int mode, int xPos, int yPos, Page* page, bool *dFirst) {
   // Make sure the header remains visible.
   mvwprintw(stdscr, 0, 0, "Group #3, editing file %s", fileName);

   wmove(stdscr, row - 1, 0);
   clrtoeol();
   wmove(stdscr, yPos, xPos);

   // If we're in editing mode we want to capture the characters
   if(ch >= 32 && ch <= 126) {
      if (mode == 'e' && xPos + 1 < MAX_COLS) {
         insertChar(page, yPos, xPos, ch);
         mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
         wmove(stdscr, yPos, xPos + 1);
         return 0;
      }
   }

   // Otherwise check for special character behavior
   switch(ch) {
      case KEY_UP:
         if(yPos > 1) {
            // Enforce upper boundary for the cursor
            if(xPos > page->sizes[yPos - 1]) xPos = page->sizes[yPos - 1];
            wmove(stdscr, yPos - 1, xPos);
         }
         break;

      case KEY_DOWN:
         // Enforce the lower boundary. If we try to go off the end of
         // the page -> update the cursor to the end of the file.
         if(xPos > page->sizes[yPos + 1]) xPos = page->sizes[yPos + 1];
         if(yPos >= page->numRows) yPos = page->numRows;
         wmove(stdscr, yPos + 1, xPos);
         break;

      case KEY_LEFT:
         // Enforce the left boundary for the cursor
         if(xPos != 0) wmove(stdscr, yPos, xPos - 1);
         break;

      case KEY_RIGHT:
         // Enforce the right boundary for the cursor
         if(xPos + 1 < MAX_COLS) {
            if (xPos < page->sizes[yPos]) wmove(stdscr, yPos, xPos + 1);
            else wmove(stdscr, yPos, xPos);
         }
         break;

      // Delete a line
      case 'd':
         if(mode == 'c' && *dFirst && page->numRows > 0) {
            *dFirst = false; // Reset delete flag
            // Delete currently selected line
            if (deleteLine(page, row, xPos, yPos)) {
               // clear each line and update with the new page lines
               for(int i = 1; i < row-2; i++) {
                  wmove(stdscr, i, 0);
                  clrtoeol();
                  mvwprintw(stdscr, i, 0, page->lines[i]);
               }
               if(yPos < page->numRows+2) wmove(stdscr, yPos, xPos);
               else wmove(stdscr, yPos-1, xPos);
            } else
               mvwprintw(stdscr, row - 1, 0, "Failed to delete position %d, %d  ", yPos, xPos);
            break;
         }

         if (mode == 'c') {
            *dFirst = true; // Set delete flag
            break;
         }

      // Quit
      case 'q':
         // Only quit if we're in command mode,
         // otherwise q is just a normal char.
         if (mode == 'c') return -1;

      // Save
      case 'w':
         // Only save if we're in command mode,
         // otherwise w is just a normal char.
         if (mode == 'c') {
            saveFile(page, fileName);
            mvwprintw(stdscr, row - 2, 0, "Saved file %s!", fileName);
            wmove(stdscr, yPos, xPos);
            break;
         }

      // Delete a character
      case KEY_BACKSPACE:
         backspace(stdscr, row, page, yPos, xPos, MAX_COLS);
         break;

      // ENTER KEY FUNCTIONALITY
      case 10:
      case KEY_ENTER:
          // clear each line and update with the new page lines
          if(yPos < row - 3) {
            newLine(page, row, xPos, yPos);

            for(int i = 1; i < row-2; i++) {
               wmove(stdscr, i, 0);
               clrtoeol();
               mvwprintw(stdscr, i, 0, page->lines[i]);
            }
            // move the cursor to the beginning of the next line
            wmove(stdscr, yPos + 1, 0);
          }
          break;

      // Find value
      case KEY_F(3):
         // Enable find and replace only in command mode.
         if (mode == 'c') {
            find_and_replace(stdscr, page, findOnly);
            break;
         }

      // Find and replace
      case KEY_F(4):
         if (mode == 'c') {
           find_and_replace(stdscr, page, findAndReplace);
           break;
         }

      case '?':
      default: break;
   }
   // Continue to next input
   return 0;
}


int main(int argc, char* argv[]) {

   // Notify the user if a file name is not provided and exit.
   if (argc != 2) {
      fprintf(stderr, "%s takes exactly one argument.", argv[0]);
      exit(1);
   }

   // Else run the editor
   int ch,
       mode = 'c';
   int y, x;
   bool dFirst = false;
   fileName = argv[1];

   // Configure application
   initscr();
   noecho();
   cbreak();
   keypad(stdscr, TRUE);

   // Get the maximum window dimensions
   getmaxyx(stdscr, row, col);

   // Set the boundaries for the cursor position
   getyx(stdscr, y, x);

   // Create a page datastructure with the dimensions for the screen
   Page page = pageInit(row, col);

   // Header line
   mvwprintw(stdscr, 0, 0, "Group #3, editing file %s", fileName);
   wmove(stdscr, 0, x);

   // Open the file and load the contents into the page.
   loadFile(&page, fileName);
   initView(&page);

   // Continue to get an input until q is provided in command mode.
   while((ch = getch())) {
      getyx(stdscr, y, x);

      // Manage mode changes:

      // ESC key sets mode to command
      if (ch == 27) {
         mode = 'c';
         // Clear the mode status
         mvwprintw(stdscr, row - 2, 0, "                        ", y, x);
         mvwchgat(stdscr, y, x, 1, A_NORMAL, 0, NULL);
         continue;
      }

      // Set editing mode
      if (mode == 'c' && ch == 'e') {
         mode = 'e';
         mvwprintw(stdscr, row - 2, 0, "----Editing---- %d, %d  ", y, x);
         mvwchgat(stdscr, y, x, 1, A_NORMAL, 0, NULL);
         continue;
      }

      // Set visual mode
      if (mode == 'c' && ch == 'v') {
         mode = 'v';
         mvwprintw(stdscr, row - 2, 0, "----Visual---- %d, %d  ", y, x);
         mvwchgat(stdscr, y, x, 1, A_NORMAL, 0, NULL);
         continue;
      }

      if (driver(ch, mode, x, y, &page, &dFirst) < 0) break;
      else refresh();
   }
   freePage(&page);
   endwin();
   return 0;
}

void initView(Page* page) {
   int rowCount = page->numRows;
   for(int i = 0; i < rowCount + 2; i++) {
     if (i == rowCount + 1) printw(page->lines[i]);
     else printw(strcat(page->lines[i], "\n"));
   }
   refresh();
}
