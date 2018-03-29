//***********************************************/
// deleteline.h:
//   Remove a line from the page.
//***********************************************/
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "page_struct.h"

//***********************************************/
// deleteLine:
//   deletes a line from the page and returns a
//   status code: 0 for fail 0 for success
//
// Parameters:
//   page: Reference to Page object
//   row: max # of rows
//   x: row # of the position of the character
//   y: column # of the position of the character
//
//***********************************************/
bool deleteLine(Page* page, int row, int xPos, int yPos);