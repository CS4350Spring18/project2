#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "page_struct.h"

//***********************************************/
// insertRow:
//   Inserts a character to position on the page
//
// Parameters:
//   page: Refernce to Page object to change
//   row: row # of the position for the character
//   col: column # of the position for the character
//   c: character to insert 
//
//***********************************************/
void insertChar(Page* page, int row, int col, char c);

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
//   MAX_COLS: maximum number of columns
//
//***********************************************/
void backspace(Page* page, int row, int col, int MAX_COLS);
