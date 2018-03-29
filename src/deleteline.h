#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "page_struct.h"

//***********************************************/
// deleteLine:
//   deletes a line from the page
//
// Parameters:
//   page: Refernce to Page object to initiate
//   row: max # of rows
//   x: row # of the position of the character
//   y: column # of the position of the character
//
//***********************************************/
void deleteLine(Page* page, int row, int x, int y);