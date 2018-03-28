#include "page_ops.h"

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
