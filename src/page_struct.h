//****************************/
// page_struct.h 
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
//****************************/
#pragma once

static const int MAX_COLS = 80;

typedef struct Page {
  char** lines;
  int* sizes;
  int numRows;
} Page;
