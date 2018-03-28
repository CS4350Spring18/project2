//****************************/
// save_file.h
//
// Design:
//   Manage open and load operations for
//   the editor.
//
//****************************/
#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "page_struct.h"

//****************************/
// saveFile:
//   Save the contents of the page to the specified
//   filename. Copy each line of the page, row-by-row
//   into the file associated with the filename.
//
// Parameters:
//   file: The file object associated with the filename. 
//   Serves as the destination for the characters on the page.
//   numRows: The number of lines in the page to load into the file.
//
//****************************/
void saveFile(Page* page, char fileName[]);
