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
static char savedString[5];
memset(copyString, 0, 5);

void updateView(Page* page);

static int driver(int ch, int mode, int xPos, int yPos, Page* page, int justChanged, int *dFirst) {
   mvwprintw(stdscr,0,0,"Group #3, editing file %s", fileName);
//   savedString[0] = malloc(60);
   if(mode == 'e') {
     mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos);
     mvwchgat(stdscr,yPos,xPos, 1, A_NORMAL, 0, NULL);
     if(xPos > page->sizes[yPos]) wmove(stdscr,yPos, page->sizes[yPos]);
     wrefresh(stdscr);
     if(justChanged) {
       return;
     }
   }
   if(mode == 'c') {
     wmove(stdscr, row-2,0);
     clrtoeol();
     mvwchgat(stdscr,yPos,xPos, 1, A_NORMAL, 0, NULL);
     if(xPos > page->sizes[yPos]) wmove(stdscr,yPos, page->sizes[yPos]);
     wrefresh(stdscr);
   }
   if(mode == 'v') {
      int count = 0;
      mvwprintw(stdscr, row-2,0,"----Visual----- %d, %d  ", yPos, xPos);
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
           if(mode == 'v'){
           //  savedString[count++] = copy(page, yPos, xPos));
             printVisual(stdscr, page, yPos, xPos);
             highlightText();
           }
           wmove(stdscr,yPos-1, xPos);
         }
         break;

      case KEY_DOWN:
         if(xPos > page->sizes[yPos+1])
           xPos = page->sizes[yPos+1];
         if( yPos >= page->numRows)
           yPos = page->numRows;
         if(mode == 'e') {
           mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos+1, xPos);
         }
         if(mode == 'v'){
            //*savedString = copy(page, yPos, xPos);
            printVisual(stdscr, page, yPos, xPos);
            highlightText();
         }
         wmove(stdscr,yPos+1, xPos);
         break;

      case KEY_LEFT:
         if(xPos != 0) {
           if(mode == 'e') {
             mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos-1);
           }
           if(mode == 'v'){
             char* tempString;
             copy(page, yPos, xPos, &savedString, &count);
             //*savedString  = page->lines[yPos];
//             memcpy(savedString, copy(page, yPos, xPos), count++);
             printVisual(stdscr, page, yPos, xPos);
             highlightText();
           }
           wmove(stdscr,yPos, xPos-1);
         }
         break;

         case KEY_RIGHT:
         //chgat(1, A_NORMAL, 0, NULL);
         //mvchgat(yPos, xPos + 1, 1, A_STANDOUT, 0, NULL);
         if(xPos+1 < MAX_COLS) {
           if(xPos < page->sizes[yPos]) {
             if(mode == 'e'){
               mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos+1);
             }
             if(mode == 'v'){
               //*savedString[count++] = copy(stdscr, yPos, xPos);
 //              memcpy(savedString, copy(page, yPos, xPos), count++);
               printVisual(stdscr, page, yPos, xPos);
               highlightText();
             } 
            wmove(stdscr,yPos, xPos+1);
           }
           else
             wmove(stdscr,yPos, xPos);
         }
         break;

      case 'q':
         if (mode == 'c') return -1;
      
      case 'p':
         if (mode == 'c')
            paste(stdscr, page, yPos, xPos, *savedString[0], count);
      break;
      case KEY_F(3):
         if (mode == 'c') {
           find_and_replace(stdscr, page, findOnly);
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
         backspace(stdscr, row, page, yPos, xPos, MAX_COLS);
         break;

      // ENTER KEY FUNCTIONALITY
      case 10:
          // clear each line and update with the new page lines
          if(yPos < row-3) {
            newLine(page, row, xPos, yPos);

            for(int i = 1; i < row-2; i++) {
              wmove(stdscr, i, 0);
              clrtoeol();
              mvwprintw(stdscr, i, 0, page->lines[i]);
            }
            // move the cursor to the beginning of the second line
            mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos+1, 0);
            wmove(stdscr,yPos+1,0);
          }
          break;

      // Press 'F4' key to switch find and replace
      case KEY_F(4):
         if (mode == 'c') {
           find_and_replace(stdscr, page, findAndReplace);
           break;
         }
      case '?': break;
      default: 
         if( ch >= 32 && ch <= 126 && xPos+1 < MAX_COLS) {
            if(mode == 'c') {
              if(ch ==  'w') {
                saveFile(page, fileName);
                mvwprintw(stdscr, row-2, 0, "Saved file %s\n", fileName);
                wmove(stdscr, yPos, xPos);
              }
              if(ch == 'q') {
                return -1;
              }
              if(ch == 'd' && !*dFirst) {
                *dFirst = 1;
                return 0;
              }
              if(ch == 'd' && *dFirst && page->numRows > 0) {
                deleteLine(page, row, xPos, yPos);
                // clear each line and update with the new page lines
                for(int i = 1; i < row-2; i++) {
                  wmove(stdscr, i, 0);
                  clrtoeol();
                  mvwprintw(stdscr, i, 0, page->lines[i]);
                }
                mvwprintw(stdscr, yPos, xPos, "%d", page->numRows);
                if(yPos < page->numRows+2)
                  wmove(stdscr, yPos, xPos);
                else
                  wmove(stdscr, yPos-1, xPos);
                *dFirst = 0;
              }
            }
            else if(ch == 'e'){
              insertChar(page, yPos, xPos, ch);
              mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
              mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos, xPos+1);
              wmove(stdscr,yPos,xPos+1);
            }
         }
         break;
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
   int y, x, justChanged = 0, dFirst = 0;
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
   wmove(stdscr, 0, x);

   // Open the file and load the contents into the page.
   loadFile(&page, fileName);
   updateView(&page);

   while((ch = getch())) {
      getyx(stdscr, y, x);

      // Manage mode changes
      if (mode != 'e'
         && ch == 'e') { mode = 'e'; justChanged = 1; }
   
      if(mode == 'c'
         && ch == 'v') mode = 'v';


      if (mode != 'c'
         && ch == 27) mode = 'c';

      //if (mode == 'e') editing(stdscr, &page);

      // Arrowkey navigation restricted to within
      // valid text area.
      if (driver(ch, mode, x, y, &page, justChanged, &dFirst) < 0) break;
      else refresh();
      justChanged = 0;
   }
   freePage(&page);
   endwin();
   return 0;
}

void updateView(Page* page) {
   int rowCount = page->numRows;
   for(int i = 0; i < rowCount+2; i++) {
     if(i == rowCount+1)
         printw(page->lines[i]);
     else
         printw(strcat(page->lines[i], "\n"));
   }
   refresh();
}
