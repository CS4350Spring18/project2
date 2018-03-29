#include "deleteline.h"

bool deleteLine(Page* page, int row, int xPos, int yPos) {
   if(yPos < row-3) {
      // clear the line completely
      for(int i = 0; i < page->sizes[yPos]; i++){
         page->lines[yPos][i] = '\0';
      }

      // move each line up one for the page
      for(int i = yPos; i < row-1; i++) {
         page->lines[i] = page->lines[i+1];
         page->sizes[i] = page->sizes[i+1];
      }
      page->numRows--;
      return true;
   }
   return false;
}
