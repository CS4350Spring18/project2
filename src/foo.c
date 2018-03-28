#include <stdio.h>
#include <stdlib.h>

#include "editing.h"
#include "load_file.h"
#include "save_file.h"
#include "page_struct.h"
#include "page_ops.h"
#include "find.h"

static int row;
static int col;
static char* fileName;

void updateView(Page* page);

static int driver(int ch, int mode, int xPos, int yPos, Page* page) {
   mvwprintw(stdscr,0,0,"Group #3, editing file %s", fileName);
   if(mode == 'e') {
     mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos);
     mvwchgat(stdscr,yPos,xPos, 1, A_NORMAL, 0, NULL);
     if(xPos > page->sizes[yPos]) wmove(stdscr,yPos, page->sizes[yPos]);
     wrefresh(stdscr);
   }
   if(mode == 'c') {
     wmove(stdscr, row-2,0);
     clrtoeol();
     mvwchgat(stdscr,yPos,xPos, 1, A_NORMAL, 0, NULL);
     if(xPos > page->sizes[yPos]) wmove(stdscr,yPos, page->sizes[yPos]);
     wrefresh(stdscr);
   }
   wmove(stdscr, row-1, 0);
   clrtoeol();
   wmove(stdscr, yPos, xPos);
   switch(ch) {
      case KEY_UP:
         if(yPos > 1) {
           //chgat(1, A_NORMAL, 0, NULL);
           //mvchgat(yPos-1, xPos, 1, A_STANDOUT, 0, NULL);
           if(xPos > page->sizes[yPos-1])
             xPos = page->sizes[yPos-1];
           if(mode == 'e') {
             mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos-1, xPos);
           }
           wmove(stdscr,yPos-1, xPos);
         }
         break;

      case KEY_DOWN:
         //chgat(1, A_NORMAL, 0, NULL);
         //mvchgat(yPos + 1, xPos, 1, A_STANDOUT, 0, NULL);
         if(xPos > page->sizes[yPos+1])
           xPos = page->sizes[yPos+1];
         if( yPos >= page->numRows)
           yPos = page->numRows;
         if(mode == 'e') {
           mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos+1, xPos);
         }
         wmove(stdscr,yPos+1, xPos);
         break;

      case KEY_LEFT:
         //chgat(1, A_NORMAL, 0, NULL);
         //mvchgat(yPos, xPos - 1, 1, A_STANDOUT, 0, NULL);
         if(xPos != 0) {
           if(mode == 'e') {
             mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos-1);
           }
           wmove(stdscr,yPos, xPos-1);
         }
         break;

      case KEY_RIGHT:
         //chgat(1, A_NORMAL, 0, NULL);
         //mvchgat(yPos, xPos + 1, 1, A_STANDOUT, 0, NULL);
         if(xPos+1 < MAX_COLS) {
           if(xPos < page->sizes[yPos]) {
             if(mode == 'e')
               mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos+1);
             wmove(stdscr,yPos, xPos+1);
           }
           else
             wmove(stdscr,yPos, xPos);
         }
         break;
      case 'w':
         if (mode == 'c') {
            saveFile(page, fileName);
            mvwprintw(stdscr, row-2, 0, "Saved file %s\n", fileName);
            wmove(stdscr, yPos, xPos);
            break;
         }
      case 'q':
         if (mode == 'c') return -1;

      case KEY_F(3):
         if (mode == 'c') {
           find_and_replace(stdscr, &page, findOnly);
           break;
         }

      case 27:
         wmove(stdscr, row-2, 0);
         clrtoeol();
         wmove(stdscr,yPos,xPos);
         break;

      case 8:
      case 127:
      case KEY_BACKSPACE:
         // If not at the left side of the line
         if(xPos != 0) {
           mvwprintw(stdscr,yPos,xPos-1," ");
           backspace(page, yPos, xPos-1);
           wmove(stdscr,yPos,xPos);
           clrtoeol();
           mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
           wmove(stdscr,yPos,xPos-1);
         }
         
         break;

      // Press 'F4' key to switch find and replace
      case KEY_F(4):
         if (mode == 'c') {
           find_and_replace(stdscr, &page, findAndReplace);
           break;
         }
      case '?': break;
      default: break;
   }
   //wrefresh(stdscr);
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
   fileName = argv[1];

   initscr();
   noecho();
   cbreak();
   keypad(stdscr, TRUE);
   getmaxyx(stdscr, row, col);

   // Create a page with the dimensions for the screen
   Page page = pageInit(row, col);

   // Header line
   mvwprintw(stdscr,0,0,"Group #3, editing file %s", fileName);
   wmove(stdscr, 1, x);

   // Open the file and load the contents into the page.
   loadFile(&page, fileName);
   updateView(&page);

   while((ch = getch())) {
      getyx(stdscr, y, x);

      // Manage mode changes
      if (mode != 'e'
         && ch == 'e') mode = 'e';

      if (mode != 'c'
         && ch == 27) mode = 'c';

      //if (mode == 'e') editing(stdscr, &page);

      // Arrowkey navigation restricted to within
      // valid text area.
      if (driver(ch, mode, x, y, &page) < 0) break;
      else refresh();
   }
   freePage(&page);
   endwin();
   return 0;
}

void updateView(Page* page) {
   int rowCount = page->numRows;
   for(int i = 0; i < rowCount; i++)
      printw(strcat(page->lines[i], "\n"));
   refresh();
}
