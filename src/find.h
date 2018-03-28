#pragma once

#include <ncurses.h>
#include "page_struct.h"

enum FindMode { findOnly, findAndReplace};

void find_and_replace(WINDOW *win, Page *page, enum FindMode findMode);
