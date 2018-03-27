//****************************/
// file_io.h
//
// Design:
//   Manage open and load operations for
//   the editor.
//
//****************************/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "page.h"

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

//****************************/
// Helper Function: openFile
//   Requires a rw mode specified for the filename.
//   Will try to open the file. Print an error message
//   if the file cannot be opened. The fn will return
//   the file associated with the filename or a null pointer.
//
// Parameters:
//   temp: The file object associated with the filename for a specified
//   mode.
//
//****************************/
FILE* openFile(char fileName[], char mode[]);
