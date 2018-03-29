//****************************/
// find.h 
//****************************/
#pragma once
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include "page_struct.h"
#include "editing.h"

typedef enum {findOnly, findAndReplace} FindMode;

//***********************************************/
// find_and_replace:
//   Highlight a the text if found. Highlight and replace
//   text if the find and replace mode is in effect.
//
//***********************************************/
void find_and_replace(WINDOW *win, Page *page, FindMode findMode);

