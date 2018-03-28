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

void backspace(Page* page, int row, int col) {
  int size = page->sizes[row];
  for(int i = col; i < size+1; i++)
    page->lines[row][i] = page->lines[row][i+1];
  page->sizes[row] = size - 1;
}
