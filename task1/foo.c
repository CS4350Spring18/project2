#include <ncurses.h>
#include <stdio.h>

int main() {
  FILE* fin = fopen("./foo.txt", "r");

  initscr();
 
  int n = 200;
  char line[n];
  
  while(fgets(line, n, fin)) {
    printw(line);
    refresh();  
  }  


  refresh();
  getch();
  endwin();
  
  return 0;
}

