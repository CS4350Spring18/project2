#include "find.h"

void exit_find_mode(WINDOW * win, int y, int x) {
   int row, col;
   getmaxyx(win, row, col);

   mvwprintw(win, row - 2, 0, "                                                     ");
   mvwprintw(win, row - 1, 0, "                                                     ");
   wmove(win, y, x);
   wrefresh(win);
}

void str_replace(char * target, const char *searchStr, const char *replaceStr) {
   char buffer[1024] = {0};
   memset(buffer, 0, 1024);

   char *insert_point = &buffer[0];
   const char *tmp = target;
   size_t searchStr_len = strlen(searchStr);
   size_t repl_len = strlen(replaceStr);

   while (1) {
      const char *p = strstr(tmp, searchStr);

      // walked past the last occurrence of searchStr
      // copy remaining part
      if (p == NULL) {
         strcpy(insert_point, tmp);
         break;
      }

      // copy part before serachStr
      memcpy(insert_point, tmp, p - tmp);
      insert_point += p - tmp;

      // copy replaceStr string
      memcpy(insert_point, replaceStr, repl_len);
      insert_point += repl_len;

      //adjust pointers
      tmp = p + searchStr_len;
   }

   // write string back to target
   strcpy(target, buffer);
}

bool handle_search_input(WINDOW *win, Page *page, int key, char searchStr[], int *searchStrPos) {
   int x, y;
   getyx(win, y, x);

   // take input
   if (key >= 32 && key <= 126) { // Standard keys
      searchStr[*searchStrPos] = key; // Assign the chars
      ++(*searchStrPos);
      searchStr[*searchStrPos]= '\0';

      addch(key); 
      wmove(win, y, x+1);
      return false;
   }

   // Backspace
   if ((key == 127 || key == 8 || key == KEY_BACKSPACE) && x != 0) {
      if (*searchStrPos > 0) --(*searchStrPos);

      // Remove last key from buffer
      searchStr[*searchStrPos] = '\0';

      // Display
      mvaddch(y, x-1, ' ');
      wmove(win, y, x-1);
      return false;
   }

   if (key == 10) {
      // Find text, and highlight matches
      size_t numRows = page->numRows;

      for (int i = 0; i < numRows; i++) {
         char *line = page->lines[i];
         char *pos = NULL;
         char *begin = line;
         while ((pos = strstr(begin, searchStr)) != NULL) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i, (pos-line), searchStr);
            wattroff(win, A_REVERSE);
            begin = pos + 1;
         }
      }

      *searchStrPos = 0;
      int row, col;
      getmaxyx(win, row, col);
      mvwprintw(win, row-1, 0, "                                                     ");
      mvwprintw(win, row-1, 0, "Replace: ");
      return true;
   }
   return false;
}

bool handle_replace_input(WINDOW *win, Page *page, int key, const char searchStr[], char replaceStr[], int* replaceStrPos) {
   int x, y;
   getyx(win, y, x);

   // take input
   if (key >= 32 && key <= 126) { // Standard keys
      replaceStr[*replaceStrPos] = key; // Assign the chars
      ++(*replaceStrPos);
      replaceStr[*replaceStrPos]= '\0';

      addch(key); 
      wmove(win, y, x+1);
      return false;
   }

   // Backspace
   if ((key == 127 || key == 8 || key == KEY_BACKSPACE) && x != 0) {
      if (*replaceStrPos > 0) --(*replaceStrPos);

      // Remove last key from buffer
      replaceStr[*replaceStrPos] = '\0';

      // Display
      mvaddch(y, x-1, ' ');
      wmove(win, y, x-1);
      return false;
   }

   if (key == 10) {
      // Find text, and highlight matches
      // Change text when enter is pressed
      size_t numRows = page->numRows;

      for (int i = 0; i < numRows; i++) {
         char *line = page->lines[i];
         char replaced[500];
         strcpy(replaced,line);

         str_replace(replaced, searchStr, replaceStr);

         // Update the buffer
         setRow(page, i, replaced);

         // Update the screen
         mvwprintw(win, i, 0, page->lines[i]);
         wclrtoeol(win);

      *replaceStrPos = 0;
      int row, col;
      getmaxyx(win, row, col);
      mvwprintw(win, row-1, 0, "                                                     ");
      mvwprintw(win, row-1, 0, "Replace: ");
      return true;

      }
      return false;
   }
}

void find_and_replace(WINDOW *win, Page *page, FindMode findMode) {
   int key;
   int y, x;
   int row, col; 
   getyx(win, y, x);
   getmaxyx(win,row,col);

   // Tell user editing mode is on
   mvwprintw(win,row-2, 0, "----Search-----");
   mvwprintw(win, row-1, 0, "Find: ");
   wrefresh(win);

   enum Mode {searchInput, replaceInput};
   enum Mode mode = searchInput;
   char searchString[100]; // String to find
   memset(searchString, 0, 100);
   char replaceString[100]; // String to replace with if chosen
   memset(replaceString, 0, 100);
   int searchStrPos = 0;
   int replaceStrPos = 0;

   while ((key = getch())) {
      // Return when Esc is pressed
      if (key == 27) {
         exit_find_mode(win, y, x);
         return;
      }
      switch(mode) {
         case searchInput:
            if (handle_search_input(win, page, key, searchString, &searchStrPos))
               if (findMode == findAndReplace) mode = replaceInput;
            else {
               exit_find_mode(win, y, x);
               return;
            }
            break;

         case replaceInput:
            if (handle_replace_input(win, page, key, searchString, replaceString, &replaceStrPos))
               return;
         default: break;
      }
   }
}

