#include "copypaste.h"


void copy(Page* page, int y, int x1, int x2, char *mainString){
   char copyString[50];
   int x, y1;
   getyx(stdscr, y1, x);
   if(x1 < x2) {
      for(int i = x1; i < x2; i++) {
        copyString[i] = page->lines[y][i]; 
      }
      copyString[x1-x2] = '\0';
   }
   else {
      for(int i = x2; i < x1; i++) {
        copyString[i] = page->lines[y][i]; 
      }
      copyString[x2-x1] = '\0';
   }
   strcpy(mainString, copyString);
}

void highlightText(){
   start_color();
   init_pair(1, COLOR_RED, COLOR_BLACK);
   attron(COLOR_PAIR(1));
   refresh();
}

void paste(WINDOW* stdscr, Page* page, char *copyString){
   int x, y, row, col, length;
   getyx(stdscr, y, x);
   length = strlen(copyString);
   getmaxyx(stdscr, row, col);


   // row would end up too long, treat as error
   if(length + page->sizes[y] > MAX_COLS) {
      mvwprintw(stdscr,row-1,0,"Error: row would be too long if pasting this string.");
      wmove(stdscr,y,x);
      refresh();
      return;
   }
   else {
      // move the current contents over 
      for(int i = x + length + 1; i > page->sizes[y] - x -1; i--) {
         page->lines[y][i] = page->lines[y][i - length -1];
      }
      page->sizes[y] = page->sizes[y] + length;

      // put in the copyString
      for(int i = x; i < x + length; i++) {
         page->lines[y][i+1] = copyString[i-x];
      }
   }

   for(int i = 1; i < row-2; i++) {
      wmove(stdscr, i, 0);
      clrtoeol();
      mvwprintw(stdscr, i, 0, page->lines[i]);
   }
   // move the cursor to the end of the line
   wmove(stdscr, y, x+length+1);

   refresh();

}


