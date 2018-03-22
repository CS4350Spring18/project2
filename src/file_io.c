#include "file_io.h"

void loadFile(char fileName[], struct Page* page) {
   int r = 0,
       c = 200;
   char line[c];
   FILE* file = openFile(fileName, "r");
   if (file != NULL) {
      // Load each line from the file into the page.
      while(fgets(line, c, file) != NULL) printw(line);
      fclose(file);
   }
}


void saveFile(char fileName[], struct Page* page) {
   fprintf(stdout, "Saving file %s\n", fileName);
   FILE* file = openFile(fileName, "r+");
   if (file != NULL) {
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

