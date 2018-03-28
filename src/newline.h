#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "page_struct.h"


//***********************************************/
// newLine:
//   inserts a new line to the page
//
// Parameters:
//   page: Refernce to Page object to initiate
//   row: max # of rows
//   col: max # of columns
//   x: row # of the position of the character
//   y: column # of the position of the character
//
//***********************************************/
void newLine(Page* page, int row, int x, int y);