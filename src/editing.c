#include "editing.h"

void editing(WINDOW* my_win, Page* page) {
   int key;
   int y, x;
   int row, col;
   getyx(my_win, y, x);
   getmaxyx(my_win, row, col);

   //Let user know editing mode is on
   mvwprintw(my_win, row-2, 0, "----Editing----");
   mvwchgat(my_win,y, x, 1, A_NORMAL, 0, NULL);
   if(x > page->sizes[y]) wmove(my_win,y, page->sizes[y]);
      wrefresh(my_win);

   //User input loop
   while((key = getch())) {
      getyx(my_win, y, x);
      //Keep navigation bounded by screen and line length
      if (x > page->sizes[y]) x = page->sizes[y];
      if (y >= page->numRows) {
         y = page->numRows - 1;
         x = page->sizes[y];
         wmove(my_win, y, x);
         wrefresh(my_win);
      }

      // Manage keyboard behavior
      if(key == KEY_UP) {
         if(x > page->sizes[y-1])
            x = page->sizes[y-1];
         wmove(my_win,y-1, x);
      }
      else if(key == KEY_DOWN){
         if(x > page->sizes[y + 1])
            x = page->sizes[y + 1];
         if(y >= page->numRows)
            y = page->numRows - 1;
         wmove(my_win, y+1, x);
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
      else if((key == 127 || key == 8 || key == KEY_BACKSPACE) && x != 0) {
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
            char first_half[50];
         //char second_half[50];

         // move each line down one for the page
         for(int i = row-3; i > y+1; i--) {
            //page->lines[i] = page->lines[i-1];
            strncpy(page->lines[i], page->lines[i-1], page->sizes[i-1]);
            page->sizes[i] = page->sizes[i-1];
         }

         strncpy(first_half, page->lines[y], x);
         //first_half[x] = '\0';
         //strncpy(second_half, page->lines[y] + x, page->sizes[y] - x);
         //second_half[page->sizes[y] - x] = '\0';
         //page->lines[y] = first_half;
         //page->lines[y+1] = second_half;
         strncpy(page->lines[y+1], page->lines[y] + x, page->sizes[y] - x);
         //page->lines[y] = first_half;
         strncpy(page->lines[y], first_half, x);
         //strncpy(page->lines[y], page->lines[y], x);
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
         if (x + 1 < MAX_COLS) {
            insert(page, y, x, key);
            mvwprintw(my_win, y, 0, page->lines[y]);
            wmove(my_win,y,x+1);
         } else {
            mvwprintw(my_win, row-2, 0, "End of row reached. Start a new line.");
            mvwchgat(my_win,y, x, 1, A_NORMAL, 0, NULL);
         }
      }
      wrefresh(my_win); 
   }
}