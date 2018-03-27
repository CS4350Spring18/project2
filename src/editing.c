#include "editing.h"

void editing(WINDOW* my_win, Page* page) {
  int key;
  int y,x;
  int row,col;
  getyx(my_win,y,x);
  getmaxyx(my_win,row,col);

  //Let user know editing mode is on
  mvwprintw(my_win,0,0,"Group #3, editing file %s", "literal_value.txt");
  mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x);
  mvwchgat(my_win,y,x, 1, A_NORMAL, 0, NULL);
  if(x > page->sizes[y]) wmove(my_win,y, page->sizes[y]);
  wrefresh(my_win);

  //User input loop
  while(key = getch()) {
    getyx(my_win, y, x);
    wmove(my_win, row-1, 0);
    clrtoeol();
    wmove(my_win, y, x);
    //Keep navigation bounded by screen and line length
    if(key == KEY_UP && y > 1) {
        if(x > page->sizes[y-1])
          x = page->sizes[y-1];
        mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y-1, x);
        wmove(my_win,y-1, x);
    }
    else if(key == KEY_DOWN){
      if(x > page->sizes[y+1])
        x = page->sizes[y+1];
      if( y >= page->numRows)
        y = page->numRows - 1;
      mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y+1, x);
      wmove(my_win,y+1, x);
    }
    else if(key == KEY_LEFT) {
      if(x != 0) {
        mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x-1);
        wmove(my_win,y, x-1);
      }
    }
    else if(key == KEY_RIGHT && x+1 < MAX_COLS) {
      if(x < page->sizes[y]) {
        mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x+1);
        wmove(my_win,y, x+1);
      }
      else {
        wmove(my_win,y, x);
      }
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
    else if(key == 8 || key == 127 || key == KEY_BACKSPACE) {
      // If not at the left side of the line
      if(x != 0) {
        //mvwprintw(my_win,y,x-1," ");
        backspace(page, y, x-1);
        mvwprintw(my_win, y, 0, page->lines[y]);
        wmove(my_win,y,x-1);
      }
      // If at the left side of the string, need to append lines
      else if(y != 0 && page->sizes[y-1] + page->sizes[y] + 1 < MAX_COLS) {
        for(int i = 0; i < page->sizes[y]; i++) {
          page->lines[y-1][page->sizes[y-1]+i] = page->lines[y][i];
        }
        int old_x = page->sizes[y-1];
        page->sizes[y-1] = page->sizes[y-1] + page->sizes[y];
        mvwprintw(my_win, y-1, 0, page->lines[y-1]);
        mvwprintw(my_win, y, 0, page->lines[y]);
        
        // move each line up one for the page
        for(int i = y; i < row-3; i++) {
          int size = 0;
          if(page->sizes[i] > page->sizes[i+1])
              size = page->sizes[i];
          else
              size = page->sizes[i+1];
          for(int j = 0; j <= size; j++)
              page->lines[i][j] = page->lines[i+1][j];
          page->sizes[i] = page->sizes[i+1];
        }

        // clear each line and update with the new page lines
        for(int i = 0; i < row-2; i++) {
          wmove(my_win, i, 0);
          clrtoeol();
          mvwprintw(my_win, i, 0, page->lines[i]);
        }
        page->numRows++;
        // move the cursor to the beginning of the second line
        mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y-1, page->sizes[y-1]);
        wmove(my_win,y-1,old_x);
      }
      // appending the line and the one below would exceed MAX_COLS
      else {
        mvwprintw(my_win,row-1,0,"Error: row would be too long if append happens.");
        wmove(my_win,y,x);
      }
    }
    //ALT_BACKSPACE
    /*else if(key == 127 && x != 0) {
      //Don't delete if at the left of screen
      backspace(page, y, x-1);
      //Need to overwrite the last character on the line, 
      //  otherwise it will remain on screen
      mvwprintw(my_win, y, page->sizes[y], " ");  
      mvwprintw(my_win, y, 0, page->lines[y]);
      wmove(my_win,y,x-1);
    }*/

    //TODO: Add Return key functionality (Task II.5)
    else if(key == 10 && y < row-3) {
      // move each line down one for the page
      for(int i = row-3; i > y+1; i--) {
        int size = 0;
        if(page->sizes[i] > page->sizes[i-1])
            size = page->sizes[i];
        else
            size = page->sizes[i-1];
        for(int j = 0; j <= size; j++)
            page->lines[i][j] = page->lines[i-1][j];
        page->sizes[i] = page->sizes[i-1];
      }

      for(int i = x; i <= page->sizes[y]; i++){
        page->lines[y+1][i-x] = page->lines[y][i];
        page->lines[y][i] = '\0';
      }

      page->sizes[y+1] = page->sizes[y] -  x;
      page->sizes[y] = x;

      // clear the first line
      wmove(my_win, y, 0);
      clrtoeol();
      // clear the second line
      wmove(my_win, y+1, 0);
      clrtoeol();
      
      // update the first line
      if(page->sizes[y] != 0)
        mvwprintw(my_win, y, 0, page->lines[y]);
      // update the second line
      if(page->sizes[y+1] != 0)
        mvwprintw(my_win, y+1, 0, page->lines[y+1]);

      // clear each line and update with the new page lines
      for(int i = 0/*y-2*/; i < row-2; i++) {
        wmove(my_win, i, 0);
        clrtoeol();
        mvwprintw(my_win, i, 0, page->lines[i]);
      }
      page->numRows++;
      // move the cursor to the beginning of the second line
      mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y+1, 0);
      wmove(my_win,y+1,0);
    }

    //If no special keys, output character
    else if( key >= 32 && key <= 126 && x+1 < MAX_COLS) {
      insert(page, y, x, key);
      mvwprintw(my_win, y, 0, page->lines[y]);
      mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x+1);
      wmove(my_win,y,x+1);
    }
    
    wrefresh(my_win); 
  }
}
