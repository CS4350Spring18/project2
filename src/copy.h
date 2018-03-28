#pragma once

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "page_struct.h"

int copy(WINDOW* my_win, int length, Page* page);

void paste(WINDOW* my_win, char myString, Page* page);

