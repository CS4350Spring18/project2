//****************************/
// Page.h 
//
// Design:
//   Keep track of each line of text with
//   a 2D array of characters
//   (or a 1D array of c-strings)
//
// Member Variables:
//  lines: 2D array of charaacters
//  sizes: the number of characters by row
//  numRows: the number of rows that currently have characters
//
//
//****************************/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <string.h>

static const int MAX_COLS = 80;

typedef struct Page {
  char** lines;
  int* sizes;
  int numRows;
} Page;

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
Page pageInit(int rows, int columns);

//***********************************************/
// freePage:
//   Initializes a Page "object" and allocates
//   memory for the arrays.
//
// Parameters:
//   page: Refernce to Page object to initiate
//   rows: # of rows in the window displaying the page
//   columns: # of columns " " " " " 
//
//***********************************************/
void freePage(Page* page);

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
void insert(Page* page, int row, int col, char c);

//***********************************************/
// setRow:
//   Replaces a line in page with a new string
//
// Parameters:
//   page: Refernce to Page object to change
//   row: row # of the line 
//   line: new string the line will be set to
//
//***********************************************/
void setRow(Page* page, int row, char line[]);


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
void backspace(Page* page, int row, int col);
