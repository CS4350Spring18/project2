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
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <string.h>

struct Page {
  char** lines;
  size_t* sizes;
  size_t numRows;
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
void pageInit(struct Page* page, int rows, int columns);

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
void insert(struct Page* page, int row, int col, char c);

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
void setRow(struct Page* page, int row, char line[]);

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
void backspace(struct Page* page, int row, int col);

