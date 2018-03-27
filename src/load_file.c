#include "load_file.h"


void loadFile(Page* page, char fileName[]) {
   int row = 0,
       col = 200;
   char buffer[col];
   FILE* file = fopen(fileName, "r");
   // Load lines from a valid file object
   if (file != NULL) {
      while(fgets(buffer, col, file))
         setRow(page, row++, buffer);
      page->numRows = row;
      fclose(file);
   // If there is no valid file object,
   // create an empty line to use.
   } else {
      setRow(page, 0, "\0");
      page->numRows = 1;
   }
}

