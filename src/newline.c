#include "newline.h"

void newLine(Page* page, int row, int xPos, int yPos) {
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
    
    int line_size = 0;
    if(page->sizes[yPos] > page->sizes[yPos+1])
      line_size = page->sizes[yPos];
    else
      line_size = page->sizes[yPos+1];
    for(int i = xPos; i <= line_size; i++){
      page->lines[yPos+1][i-xPos] = page->lines[yPos][i];
      page->lines[yPos][i] = '\0';
    }
    page->lines[yPos][xPos] = '\n';

    page->sizes[yPos+1] = page->sizes[yPos] -  xPos;
    page->sizes[yPos] = xPos;

    page->numRows++;
  }
}
