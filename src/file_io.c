#include "file_io.h"


void loadFile(Page* page, char fileName[]) {
   int row = 0,
       col = 200;
   char buffer[col];
   FILE* file = openFile(fileName, "r");
   if (file != NULL) {
      // Load each line from the file into the page.
      while(fgets(buffer, col, file) != NULL)
         setRow(page, row++, buffer);
      page->numRows = row;
      fclose(file);
   }
}


void saveFile(Page* page, char fileName[]) {
   FILE* file = openFile(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      // Insert each row from page into the file.
      for (int i = 0; i < numRows; i++){
         char temp[page->sizes[i]];
         strncpy(temp, page->lines[i], page->sizes[i]);
         fputs(strcat(temp, "\n"), file);
      }
      fclose(file);
   }
}


FILE* openFile(char fileName[], char mode[]) {
   return fopen(fileName, mode);
}
