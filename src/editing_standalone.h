#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "page.h"

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
