#include "file_io.h"

void loadFile(Page* page, char fileName[]) {
   int row = 0,
       col = 200;
   char buffer[col];
   FILE* file = _openFile(fileName, "r");
   // Load lines from a valid file object
   if (file != NULL) {
      while(fgets(buffer, col, file) != NULL)
         setRow(page, row++, buffer);
      page->numRows = row;
      fclose(file);
   } else {
      // If there is no valid file object,
      // create an empty line to use.
      setRow(page, 0, "\0");
      page->numRows = 1;
   }
}


void saveFile(Page* page, char fileName[]) {
   FILE* file = _openFile(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      for (int i = 0; i <= numRows; i++) {
         if(page->lines[i][0] == 0) fputs("\n", file);
         else fputs(page->lines[i], file);
      }
      fclose(file);
   }
}


FILE* _openFile(char fileName[], char mode[]) {
   return fopen(fileName, mode);
}

