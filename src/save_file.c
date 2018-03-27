#include "save_file.h"

void saveFile(Page* page, char fileName[]) {
   FILE* file = fopen(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      for (int i = 0; i <= numRows; i++) {
         if(page->lines[i][0] == 0) fputs("\n", file);
         else fputs(page->lines[i], file);
      }
      fclose(file);
   }
}

