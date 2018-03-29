#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "page_struct.h"

// only copying from one line
void copy(Page* page, int y, int x1, int x2, char *mainString);

void highlightText();

void paste(WINDOW* stdscr, Page* page, char *copyString);
