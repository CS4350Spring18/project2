#include "editing.h"

void editing(WINDOW* my_win, Page* page) {
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
  while((key = getch())) {
    getyx(my_win, y, x);
    //Keep navigation bounded by screen and line length
    if(key == KEY_UP) {
      if(x > page->sizes[y-1])
        x = page->sizes[y-1];
      mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  %d", y-1, x, page->numRows);
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
      if(x != 0)
        mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x-1);
      wmove(my_win,y, x-1);
    }
    else if(key == KEY_RIGHT) {
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
      if(x != 0) {
        mvwprintw(my_win,y,x-1," ");
        backspace(page, y, x-1);
        wmove(my_win,y,x-1);
      }
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
    else if(key == 10) {

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
    else if( key >= 32 && key <= 126) {
      insertChar(page, y, x, key);
      mvwprintw(my_win, y, 0, page->lines[y]);
      mvwprintw(my_win,row-2,0,"----Editing---- %d, %d  ", y, x+1);
      wmove(my_win,y,x+1);
    }
    
    wrefresh(my_win); 
  }
}

void insertChar(Page* page, int row, int col, char c) {
  int rowSize = page->sizes[row];

   // Check that we aren't adding a character
   // beyond the end of the array.
   if (col < MAX_COLS
      && (rowSize + 1 < MAX_COLS)) {
      memmove(
         page->lines[row] + col + 1,
         page->lines[row] + col,
         MAX_COLS - (col + 1)
      );
      page->lines[row][col] = c;
      page->sizes[row]++;
   }
}

void setRow(Page* page, int row, char line[]) {
   page->sizes[row] = strlen(line);
   if (line[page->sizes[row] - 1] == '\n')
      page->sizes[row]--;
   strncpy(page->lines[row], line, page->sizes[row]);
}

void backspace(Page* page, int row, int col) {
  int size = page->sizes[row];
  for(int i = col; i < size+1; i++)
    page->lines[row][i] = page->lines[row][i+1];
  page->sizes[row] = size - 1;
}
