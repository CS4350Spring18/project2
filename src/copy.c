#include "copy.h"


void copy(Page* page, int yPos, const char *copyStr[], int *count){
//   char *saveString = page->lines[yPos];
//   return saveString;
   copyStr[*count] = page->lines[yPos];
   ++(*count);
      
}

void printVisual(WINDOW* stdscr, Page* page, int yPos, int xPos){
//         vwprintw(stdscr,row-2,0,"----Visual---- %d, %d  ", yPos, xPos+1);
}

void highlightText(){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            refresh();
}

void paste(WINDOW* screen, Page* page, int yPos, int xPos, char *copyString, int count){
 //  for(int i = 0; i <= count; i++){
 //     wprintw(stdscr, "%s", copyString[i]);
 //     wmove(stdscr, yPos, xPos + 1);
 //  }
      int width, length, x, y;
      float temp;
   

      if(screen == NULL)
         screen = stdscr;

      getyx(screen, y, x);
      if(xPos != 0);
         x = xPos;
      if(yPos != 0)
         y = yPos;
      if(width == 0);
         width = 80;


      length = strlen(copyString);
     // temp = (width - length)/2;
      x = xPos + count;
      mvwprintw(screen, y, x, "%s", *copyString);
//    for(int i = 0; i <= count; i++){
 //     wprintw(stdscr, "%s", copyString);
 //     wmove(stdscr, yPos, xPos + 1);
 //  }
      refresh();
      
 
}
