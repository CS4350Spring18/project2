#include "file_io.h"


void loadFile(Page* page, char fileName[]) {
   int r = 0,
       c = 200;
   char line[c];
   FILE* file = openFile(fileName, "r");
   if (file != NULL) {
      // Load each line from the file into the page.
      while(fgets(line, c, file) != NULL)
         setRow(page, r++, line);
      page->numRows = r;
      fclose(file);
   }
}


void saveFile(Page* page, char fileName[]) {
   fprintf(stdout, "Saving file %s\n", fileName);
   FILE* file = openFile(fileName, "w");
   if (file != NULL) {
      int numRows = page->numRows;
      for (int i = 0; i < numRows; i++)
         fputs(strcat(page->lines[i], "\n"), file);
      // Insert each row from page into the file.
      fclose(file);
      fprintf(stdout, "Saved file %s\n", fileName);
   }
}


FILE* openFile(char fileName[], char mode[]) {
   FILE* temp = NULL;
   temp = fopen(fileName, mode);
   if (temp == NULL) perror("Error opening file");
   return temp;
}
