//****************************/
// page_init.h 
//
// Design:
//   Initialize the rows and columns inside
//   the data structure.
//
//****************************/
#pragma once

#include <stdlib.h>
#include "page_struct.h"

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
