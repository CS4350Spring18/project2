#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "editing.h"

int main() {
//Print contents of dummy file to the screen
//TODO: Change to update the page as well as the screen
  FILE* fin = fopen("./text.txt", "w+");

  initscr();
  printw("Hello World !!!");
  int n = 200;
  char line[n];
  
  while(fgets(line, n, fin)) {
    printw(line);
    refresh();  
  }  

//Default "Command Mode"
//only accepts certain keys for input
//cursor highlights text instead of underlines
  noecho();
  raw();
  keypad(stdscr, TRUE);
  int key;
  int y,x;
  int row,col;
  getyx(stdscr,y,x);
  getmaxyx(stdscr,row,col);

  struct Page my_page;
  
  pageInit(&my_page, row, col);
 
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

    //Press 'q' key to quit application
    if(key == 113)
      break;
    //Press 'e' key to switch to editing mode
    if(key == 101)
      editing(stdscr, &my_page);
 
    refresh();
  }

  endwin();
  
  return 0;
}

