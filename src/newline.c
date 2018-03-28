#include "newline.h"

void newLine(Page* page, int row, int x, int y) {
  if(yPos < row-3) {
    // move each line down one for the page
    for(int i = row-3; i > yPos+1; i--) {
      int size = 0;
      if(page->sizes[i] > page->sizes[i-1])
        size = page->sizes[i];
      else
          size = page->sizes[i-1];
      for(int j = 0; j <= size; j++)
        page->lines[i][j] = page->lines[i-1][j];
      page->sizes[i] = page->sizes[i-1];
    }

    for(int i = xPos; i <= page->sizes[yPos+1]; i++){
      page->lines[yPos+1][i-xPos] = page->lines[yPos][i];
      page->lines[yPos][i] = '\0';
    }

    page->sizes[yPos+1] = page->sizes[yPos] -  xPos;
    page->sizes[yPos] = xPos;

    page->numRows++;
  }
}
