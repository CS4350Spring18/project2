#include "save_file.h"

void saveFile(Page* page, char fileName[]) {
   FILE* file = fopen(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      for (int i = 1; i <= numRows+1; i++) {
         if(page->lines[i][0] == 0 && i != numRows+1) fputs("\n", file);
         else fputs(page->lines[i], file);
      }
      fclose(file);
   }
}

