#pragma once

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "page.h"

int copy(WINDOW* my_win, int &length, struct Page* page);

void paste(WINDOW* my_win, char &myString, struct Page* page);

