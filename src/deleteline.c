#include "deleteline.h"

void deleteLine(Page* page, int row, int xPos, int yPos) {
  if(yPos < row-3) {
    // // move each line down one for the page
    // for(int i = row-3; i > yPos+1; i--) {
    //   int size = 0;
    //   if(page->sizes[i] > page->sizes[i-1])
    //     size = page->sizes[i];
    //   else
    //       size = page->sizes[i-1];
    //   for(int j = 0; j <= size; j++)
    //     page->lines[i][j] = page->lines[i-1][j];
    //   page->sizes[i] = page->sizes[i-1];
    // }

    // clear the line completely
    for(int i = 0; i < page->sizes[yPos]; i++){
      page->lines[yPos][i] = '\0';
    }

    // move each line up one for the page
    for(int i = yPos; i < row-1; i++) {
      page->lines[i] = page->lines[i+1];
      page->sizes[i] = page->sizes[i+1];
    }

    //page->lines[row-1] = '\0';
    //page->sizes[row-1] = 0;


    page->numRows--;
  }
}
