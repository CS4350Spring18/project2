#pragma once

#include "page.h"

enum FindMode { findOnly, findAndReplace};

void find_and_replace(WINDOW *win, struct Page *page, enum FindMode findMode);
