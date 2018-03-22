#include "page.h"

void pageInit(struct Page* page, int rows, int columns) {

  //Initiate arrays with the size large enough to fill the screen
  page->lines = malloc( rows * sizeof(char *));
  page->sizes = malloc( rows * sizeof(int));
 
  for(int i = 0; i < rows; i++) { 
    page->sizes[i] = 0;
    page->lines[i] = malloc( columns * sizeof(char));
    page->lines[i][0] = '\0';
  }

  page->numRows = 0;
}

void insert(struct Page* page, int row, int col, char c) {
  int size = page->sizes[row];

  for(int i = size; i >= col; i--) {
    page->lines[row][i+1] = page->lines[row][i];
    if(i == col)
      page->lines[row][i] = c;
  }

  page->sizes[row] = size + 1;
}

void setRow(struct Page* page, int row, char line[]) {
   page->lines[row] = line;
   page->sizes[row] = strlen(line);
}

void backspace(struct Page* page, int row, int col) {
  int size = page->sizes[row];
  
  for(int i = col; i < size+1; i++) {
    page->lines[row][i] = page->lines[row][i+1];
  } 

  page->sizes[row] = size - 1;
}

