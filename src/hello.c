#include <stdio.h>
#include <stdlib.h>

#include "editing.h"
#include "file_io.h"
#include "page.h"

void updateView(Page* page);

int main(int argc, char* argv[]) {

   if (argc != 2) {
      fprintf(stderr, "%s takes exactly one argument.", argv[0]);
      exit(1);
   }
   char* fileName = argv[1];

   initscr();

   //Default "Command Mode"
   //only accepts certain keys for input
   //cursor highlights text instead of underlines
   noecho();
   raw();
   keypad(stdscr, TRUE);
   int key;
   int y, x;
   int row, col;

   // Retrieve information about the screen
   getyx(stdscr, y, x);
   getmaxyx(stdscr, row, col);

   // Create a page with the initial row
   // and column information.
   Page my_page = pageInit(row, col);

   // Try to open the file and get the contents.
   loadFile(&my_page, fileName);

   // Update the view if the file has contents.
   updateView(&my_page);

   while((key = getch())) {
      getyx(stdscr, y, x);

      //Navigation with Arrowkeys
      //Isn't bound by page structure, might want to change to restrict movement
      if(key == KEY_UP) {
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(y-1, x, 1, A_STANDOUT, 0, NULL);     
      }
      if(key == KEY_DOWN){
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(y+1, x, 1, A_STANDOUT, 0, NULL);
      }
      if(key == KEY_LEFT) {
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(y, x-1, 1, A_STANDOUT, 0, NULL);
      }
      if(key == KEY_RIGHT) {
         chgat(1, A_NORMAL, 0, NULL);
         mvchgat(y, x+1, 1, A_STANDOUT, 0, NULL);
      }

      //Press 'w' key to save the file
      if (key == 119) {
         saveFile(&my_page, fileName);
         mvwprintw(stdscr, row-2, 0, "Saved file %s\n", fileName);
         mvwchgat(stdscr, y, x, 1, A_NORMAL, 0, NULL);
      }
      //Press 'q' key to quit application
      if (key == 113) break;
      //Press 'e' key to switch to editing mode
      if (key == 101) editing(stdscr, &my_page);
      refresh();
      //Press 'v' key to switch to visual mode
      if (key == 118) visual(stdscr, &my_page);
      refresh();
   }
   freePage(&my_page);
   endwin();
   exit(0);
}

void updateView(Page* page) {
   int rowCount = page->numRows;
   if (rowCount > 0) {
      // Add a newline to the end of the line
      for(int i = 0; i < rowCount - 1; i++)
         printw(strcat(page->lines[i], "\n"));
      // Don't add a newline to the last line
      // This prevents the cursor from rolling
      // over to a newline at the EOF.
      printw(page->lines[rowCount - 1]);
   }
}
