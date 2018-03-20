#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "page.h"

void editing(WINDOW* my_win, struct Page* page) {
  int key;
  int y,x;
  int row,col;
  getyx(my_win,y,x);
  getmaxyx(my_win,row,col);

  //Let user know editing mode is on
  mvwprintw(my_win,row-2,0,"----Editing----");
  mvwchgat(my_win,y,x, 1, A_NORMAL, 0, NULL);
  if(x > page->sizes[y]) wmove(my_win,y, page->sizes[y]);
  wrefresh(my_win);

  //User input loop
  while(key = getch()) {
    getyx(my_win, y, x);
    //Keep navigation bounded by screen and line length
    if(key == KEY_UP) {
      if(x > page->sizes[y-1])
        x = page->sizes[y-1];
      wmove(my_win,y-1, x);
    }
    else if(key == KEY_DOWN){
      if(x > page->sizes[y+1])
        x = page->sizes[y+1];
      wmove(my_win,y+1, x);
    }
    else if(key == KEY_LEFT) {
      wmove(my_win,y, x-1);
    }
    else if(key == KEY_RIGHT) {
      if(x < page->sizes[y]) 
        wmove(my_win,y, x+1);
    }
    //Escape Key
    //quit editing mode back to command mode, remove tag at the bottom 
    else if(key == 27) {
      mvwprintw(my_win,row-2,0,"                                                     ");
      wmove(my_win,y,x);
      wrefresh(my_win);
      return;
    }
    //KEY_BACKSPACE
    else if(key == 8) {
      mvwprintw(my_win,y,x-1," ");
      wmove(my_win,y,x-1);
    }
    //ALT_BACKSPACE
    else if(key == 127 && x != 0) {
      //Don't delete if at the left of screen
      backspace(page, y, x-1);
      //Need to overwrite the last character on the line, 
      //  otherwise it will remain on screen
      mvwprintw(my_win, y, page->sizes[y], " ");  
      mvwprintw(my_win, y, 0, page->lines[y]);
      wmove(my_win,y,x-1);
    }

    //TODO: Add Return key functionality (Task II.5)

    //If no special keys, output character
    else if( key >= 32 && key <= 126) {
      insert(page, y, x, key);
      mvwprintw(my_win, y, 0, page->lines[y]);
      wmove(my_win,y,x+1);
    }
    
    wrefresh(my_win); 
  }
}
