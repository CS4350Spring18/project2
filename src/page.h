//****************************/
// Page.h 
//
// Design:
//   Keep track of each line of text with
//   a 2D array of characters
//   (or a 1D array of c-strings)
//
//
//
//****************************/


#include <stdio.h>
#include <stdlib.h>

struct Page {
  char** lines;
  int* sizes;
};

//***********************************************/
// pageInit:
//   Initializes a Page "object" and allocates
//   memory for the arrays.
//
// Parameters:
//   page: Refernce to Page object to initiate
//   rows: # of rows in the window displaying the page
//   columns: # of columns " " " " " 
//
//***********************************************/
void pageInit(struct Page* page, int rows, int columns) {

  //Initiate arrays with the size large enough to fill the screen
  page->lines = malloc( rows * sizeof(char *));
  page->sizes = malloc( rows * sizeof(int));
 
  for(int i = 0; i < rows; i++) { 
    page->sizes[i] = 0;
    page->lines[i] = malloc( columns * sizeof(char));
    page->lines[0] = '\0';
  }

}

//***********************************************/
// insert:
//   Inserts a character to position on the page
//
// Parameters:
//   page: Refernce to Page object to change
//   row: row # of the position for the character
//   col: column # of the position for the character
//   c: character to insert 
//
//***********************************************/
void insert(struct Page* page, int row, int col, char c) {
  int size = page->sizes[row];

  for(int i = size; i >= col; i--) {
    page->lines[row][i+1] = page->lines[row][i];
    if(i == col)
      page->lines[row][i] = c;
  }

  page->sizes[row] = size + 1;
}

//***********************************************/
// backspace:
//   Removes a charcter from a position on the page
//
// Parameters:
//   page: Refernce to Page object to initiate
//   row: row # of the position of the character
//   col: column # of the position of the character
//
//***********************************************/
void backspace(struct Page* page, int row, int col) {
  int size = page->sizes[row];
  
  for(int i = col; i < size+1; i++) {
    page->lines[row][i] = page->lines[row][i+1];
  } 

  page->sizes[row] = size - 1;
}

