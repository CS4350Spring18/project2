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

    // clear the first line
    wmove(stdscr, yPos, 0);
    clrtoeol();
    // clear the second line
    wmove(stdscr, yPos+1, 0);
    clrtoeol();
    
    // update the first line
    if(page->sizes[yPos] != 0)
      mvwprintw(stdscr, yPos, 0, page->lines[yPos]);
    // update the second line
    if(page->sizes[yPos+1] != 0)
      mvwprintw(stdscr, yPos+1, 0, page->lines[yPos+1]);

    page->numRows++;
  }
}
