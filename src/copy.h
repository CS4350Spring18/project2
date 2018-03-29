#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "page_struct.h"


char *copy(Page* page, int yPos, int xPos);

void printVisual(WINDOW* stdscr, Page* page, int yPos, int xPos);

void highlightText();

void paste(WINDOW* stdscr, Page* page, int yPos, int xPos, char *copyString, int count);
