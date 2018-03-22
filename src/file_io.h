//****************************/
// file_io.h 
//
// 
//
//
//****************************/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include "page.h"

/* loadFile opens the provided fileName
 * and loads the data line by line into the page.
 */
void loadFile(char fileName[], struct Page* page);

/*
 *
 */
void saveFile(char fileName[], struct Page* page);

/*
 *
 */
FILE* openFile(char fileName[], char mode[]);
