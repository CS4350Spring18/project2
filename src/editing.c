#include "editing.h"

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

void backspace(WINDOW* stdscr, int row Page* page, int yPos, int xPos, int MAX_COLS) {
   // If not at the left side of the line
   if(xPos != 0) {
     mvwprintw(stdscr,yPos,xPos-1," ");
     // backspace(page, yPos, xPos-1);
     int size = page->sizes[yPos];
     for(int i = xPos; i < size+1; i++)
       page->lines[yPos][i] = page->lines[yPos][i+1];
     page->sizes[yPos] = size - 1;
     wmove(stdscr,yPos,xPos);
     clrtoeol();
     mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
     wmove(stdscr,yPos,xPos-1);
   }
   // If at the left side of the string, need to append lines
   else if(yPos > 1 && page->sizes[yPos-1] + page->sizes[yPos] + 1 < MAX_COLS) {
     for(int i = 0; i < page->sizes[yPos]; i++) {
       page->lines[yPos-1][page->sizes[yPos-1]+i] = page->lines[yPos][i];
     }
     int old_xPos = page->sizes[yPos-1];
     page->sizes[yPos-1] = page->sizes[yPos-1] + page->sizes[yPos];
     mvwprintw(stdscr, yPos-1, 0, page->lines[yPos-1]);
     mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
     
     // move each line up one for the page
     for(int i = yPos; i < row-3; i++) {
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
     for(int i = 1; i < row-2; i++) {
       wmove(stdscr, i, 0);
       clrtoeol();
       mvwprintw(stdscr, i, 0, page->lines[i]);
     }
     page->numRows--;
     // move the cursor to the beginning of the second line
     mvwprintw(stdscr,row-2,0,"----Editing---- %d, %d  ", yPos-1, page->sizes[yPos-1]);
     wmove(stdscr,yPos-1,old_xPos);
   }
   // appending the line and the one below would exPosceed MAX_COLS
   else {
     mvwprintw(stdscr,row-1,0,"Error: row would be too long if append happens.");
     wmove(stdscr,yPos,xPos);
}
}