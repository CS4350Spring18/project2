#include "file_io.h"


void loadFile(Page* page, char fileName[]) {
   int c,
       col,
       row = 0;
   //char buffer[col];
   FILE* file = _openFile(fileName, "r");
   if (file != NULL) {
      // Load each line from the file into the page.
      //int c, counter = 0;

      while ( (c = fgetc (file)) != EOF ) {
         col = 0;
         if ( c == '\n' ) insert(page, col++, row++, '\0');
         else insert(page, col, row++, c);
      }

      /*while(fgets(buffer, col, file)) {
         if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
         setRow(page, row++, buffer);
      }*/
      page->numRows = row;
      fclose(file);
   } else {
      insert(page, 0, 0, '\0');
      page->numRows = 1;
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
      for (int i = 0; i < numRows; i++){
         char temp[page->sizes[i]];
         strncpy(temp, page->lines[i], page->sizes[i]);
         fputs(strcat(temp, "\n"), file);
      }
      fclose(file);
   }
}


FILE* _openFile(char fileName[], char mode[]) {
   return fopen(fileName, mode);
}
