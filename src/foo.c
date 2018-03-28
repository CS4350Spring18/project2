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
static WINDOW* screen;

void updateView(Page* page);

static int driver(int ch, int mode, int xPos, int yPos, Page* page) {
   int count = 1;
   char* savedText[count];
   char* copiedText[count];
   switch(ch) {
      case KEY_UP:
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(yPos-1, xPos, 1, A_STANDOUT, 0, NULL);

         if(mode == 'v'){
            //highlight text
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            //copy text
           // winnstr(screen, savedText[count], yPos);
            savedText[count] = winch(screen);
            refresh();
            count++;
         }
         break;

      case KEY_DOWN:
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(yPos + 1, xPos, 1, A_STANDOUT, 0, NULL);
     
         if(mode == 'v'){
            //highlight text
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            //copy text
           // winnstr(screen, savedText[count], yPos);
            savedText[count] = winch(screen);
            refresh();
            count++;
         }
         break;

      case KEY_LEFT:
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(yPos, xPos - 1, 1, A_STANDOUT, 0, NULL);

         if(mode == 'v'){
            //highlight text
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            //copy text
            savedText[count] = winch(screen);
            refresh();
            count++;
         }
         break;

      case KEY_RIGHT:
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(yPos, xPos + 1, 1, A_STANDOUT, 0, NULL);
             
         if(mode == 'v'){
            //highlight text
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            //copy text
      //      winnstr(screen, savedText[count], yPos);
            savedText[count] = winch(screen);
            refresh();
            count++;
         }   
         break;

      case 'w':
         if (mode == 'c') {
            saveFile(page, fileName);
            mvwprintw(stdscr, row-2, 0, "Saved file %s\n", fileName);
            wmove(stdscr, yPos - 1, xPos);
            break;
         }

      case '[':
         if (mode == 'v'){
          //  *copiedText = *savedText;
            savedText[1] = 'n';
            break;
         }
         break;
      //case to paste text in mode v
      case ']':
         if (mode == 'c'){
            savedText[0] = 'y';
            for(int i = 0; i <= count; i++){
              // if ( xPos > page->sizes[yPos]){
              //    wprintw(screen, "%c", savedText[i]);
              //    wmove(screen, yPos, xPos + 1);
              // }
              // else{
              wprintw(screen, "%c", savedText[i]);
              wmove(screen, yPos, xPos + 1);
              // }
            }
            break;
         }
         break;
      case 'q':
         if (mode == 'c') return -1;

      case KEY_F(3):
         find_and_replace(stdscr, page, findOnly);
         break;

      // Press 'F4' key to switch find and replace
      case KEY_F(4):
         find_and_replace(stdscr, page, findAndReplace);
         break;

      case '?': break;
      default: break;
   }
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
   screen = stdscr;
   noecho();
   cbreak();
   keypad(screen, TRUE);
   getmaxyx(screen, row, col);

   // Create a page with the dimensions for the screen
   Page page = pageInit(row, col);

   // Open the file and load the contents into the page.
   loadFile(&page, fileName);
   updateView(&page);

   while((ch = getch())) {
      getyx(screen, y, x);

      // Manage mode changes
      if (mode != 'e'
         && ch == 'e') mode = 'e';

      if (mode != 'c'
         && ch == 27) mode = 'c';

      if (mode == 'c' 
         && ch == 'v') mode = 'v';

      if (mode == 'e') editing(screen, &page);

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
