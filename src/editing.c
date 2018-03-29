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

void backspace(Page* page, int row, int col, int MAX_COLS) {
  if(xPos != 0) {
    int size = page->sizes[row];
    for(int i = col; i < size+1; i++)
      page->lines[row][i] = page->lines[row][i+1];
    page->sizes[row] = size - 1;
  }
  // If at the left side of the string, need to append lines
  else if(yPos > 1 && page->sizes[yPos-1] + page->sizes[yPos] + 1 < MAX_COLS) {
    for(int i = 0; i < page->sizes[yPos]; i++) {
      page->lines[yPos-1][page->sizes[yPos-1]+i] = page->lines[yPos][i];
    }
    int old_xPos = page->sizes[yPos-1];
    page->sizes[yPos-1] = page->sizes[yPos-1] + page->sizes[yPos];

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
    page->numRows--;
  }
}