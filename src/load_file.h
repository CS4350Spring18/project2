//****************************/
// load_file.h
//
// Design:
//   Manage load operations for the editor.
//
//****************************/
#pragma once

#include <stdio.h>

#include "page_struct.h"
#include "page_ops.h"
#include "editing.h"

//****************************/
// loadFile:
//   Open the file associated with filename.
//   Load each line of the file into the data
//   structure for the page. Print error message if
//   the filename is not associated with a valid file
//   object.
//
// Parameters:
//   r: Counts the row position for the cursor in the
//   file.
//   c: # of characters to read from the row
//   file: file object associated with the filename.
//   Contains the characters to be loaded into the page.
//
//****************************/
void loadFile(Page* page, char fileName[]);

