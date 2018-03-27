#include "file_io.h"

void loadFile(Page* page, char fileName[]) {
   int r = 0,
       c = 200;
   char line[c];
   FILE* file = _openFile(fileName, "r");
   if (file != NULL) {
      // Load each line from the file into the page.
      while(fgets(line, c, file) != NULL)
         setRow(page, r++, line);
      page->numRows = r;
      fclose(file);
   }
}


void saveFile(Page* page, char fileName[]) {
   FILE* file = _openFile(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      for (int i = 0; i <= numRows; i++) {
         if(page->lines[i][0] == 0)
           fputs("\n", file);
         else
           fputs(page->lines[i], file);
      }
      // Insert each row from page into the file.
      fclose(file);
   }
}


FILE* _openFile(char fileName[], char mode[]) {
   FILE* temp = NULL;
   temp = fopen(fileName, mode);
   if (temp == NULL) perror("Error opening file");
   return temp;
}

