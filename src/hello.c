#include <stdio.h>
#include <stdlib.h>

#include "editing.h"
#include "file_io.h"
#include "page.h"

void updateView(struct Page* page);

int main(int argc, char* argv[]) {

   if (argc != 2) {
      fprintf(stderr, "%s takes exactly one argument.", argv[0]);
      exit(1);
   }
//Print contents of dummy file to the screen
//TODO: Change to update the page as well as the screen

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
  getyx(stdscr, y, x);
  getmaxyx(stdscr, row, col);

  struct Page my_page;

  pageInit(&my_page, row, col);

   // Scales code section
   // open the file and load the contents into the page.
   loadFile(argv[1], &my_page);
   updateView(&my_page);


  while(key = getch()) {
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
    if (key == 119) saveFile(argv[1], &my_page);
    //Press 'q' key to quit application
    if (key == 113) break;
    //Press 'e' key to switch to editing mode
    if (key == 101) editing(stdscr, &my_page);
 
    refresh();
  }
   //saveFile(argv[1], &my_page);
  endwin();
  
  return 0;
}

void updateView(struct Page* page) {
   int rowCount = page->numRows;
   printf("%d\n", rowCount);
   for(int i = 0; i < rowCount; i++)
      printw(page->lines[i]);
}
