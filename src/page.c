#include "page.h"

Page pageInit(int rows, int columns) {

   //Initiate arrays with the size large enough to fill the screen
   Page page = {
      (char **)malloc( rows * sizeof(char *)),
      (int *)malloc( rows * sizeof(int)),
      0
   };

   for(int i = 0; i < rows; i++) { 
      page.sizes[i] = 0;
      page.lines[i] = (char *)malloc( columns * sizeof(char));
      page.lines[i][0] = '\0';
      page.numRows++;
   }
   return page;
}

void freePage(Page* page) {
   int numRows = page->numRows;
   // Free the array that holds the size of each line
   // and the array that holds the lines.
   for (int i = 0; i < numRows; i++)
      free(page->lines[i]);
   free(page->lines);
   free(page->sizes);
}

void insert(Page* page, int row, int col, char c) {
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
      // If the row is at the front of the array
      //for (int i = rowSize; i >= col; i--) {
      //   page->lines[row][i+1] = page->lines[row][i];
      //   if (i == col) page->lines[row][i] = c;
      //}
      //page->sizes[row]++;
   // If beyond the end of the array,
   // move to the next line.
   } else {
      
   }
   
  //page->sizes[row] = size + 1;
   //if(c != '\n') {
    //page->sizes[row] = size + 1;
 // }

}

void setRow(Page* page, int row, char line[]) {
   page->sizes[row] = strlen(line);
   if (line[page->sizes[row] - 1] == '\n')
      page->sizes[row]--;
   strncpy(page->lines[row], line, page->sizes[row]);
}

void backspace(struct Page* page, int row, int col) {
  int size = page->sizes[row];
  for(int i = col; i < size+1; i++)
    page->lines[row][i] = page->lines[row][i+1];
  page->sizes[row] = size - 1;
}


