#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <page.h>

void visual(WINDOW* my_win, struct Page* page){
	char string[]; 	

	int key;
	int y,x;
	int row,col;
	getyx(my_win,y,x);
	getmaxyx(my_win,row,col);

	//let user know visual mode is on
	mvwprintw(my_win, row-2, 0,"----VISUAL----");
	mvwchgat(my_win, y, x, 1, A_NORMAL, 0 , NULL);
	if(x > page->sizes[y]) wmove(my_win,y, page->sizes[y]);
	wrefresh(my_win);


	//user input loop
	while(key = getch()){
		getyx(my_win, y, x);

		if(key == KEY_UP){
			if(x > page->sizes[y-1])
				x = page->sizes[y-1];

				//put highlighted text into array
				mvgetch(y, x);
				string[y+x] = mvgetch(my_win, y, x); //needtodowholeline

				//highlight text
				start_color();
				init_pair(1, COLOR_RED, COLOR_BLACK);

				attron(COLOR_PAIR(1));
				printw(string[y+x];
				refresh();

				//move cursor
				wmove(my_win, y-1, x);
		}

		if(key == KEY_DOWN){
			if(x > page->sizes[y+1])
				x = page->sizes[y+1];
				//put highlighted text into array
				mvgetch(y, x);
				string[y+x] = mvgetch(my_win, y, x); //needtodowholeline
			
				//highlight text
				start_color();
				init_pair(1, COLOR_RED, COLOR_BLACK);

				attron(COLOR_PAIR(1));
				printw(string[y+x];
				refresh();

		
				//move cursor
				wmove(my_win, y+1, x)
		}

		if(key == KEY_RIGHT){
			if(x < page->sizes[y])
				//put highlighted text into array
				mvgetch(y, x);
				string[y+x] = mvgetch(my_win, y, x); //needtodowholine
			
				//highlight text
				start_color();
				init_pair(1, COLOR_RED, COLOR_BLACK);

				attron(COLOR_PAIR(1));
				printw(string[y+x];
				refresh();

				//move cursor
				wmove(my_win, y, x+1)		
	
		}
		
		if(key == KEY_LEFT){
			if(x != 0)
				//put highlighted text into array
				mvgetch(y, x);
				string[y+x] = mvgetch(my_win, y, x); //needtodowholine
			
				//highlight text
				start_color();
				init_pair(1, COLOR_RED, COLOR_BLACK);

				attron(COLOR_PAIR(1));
				printw(string[y+x];
				refresh();

				//move cursor
				wmove(my_win, y, x-1)

		}
	

		//ESCAPE goes back to command line	
		else if(key == 27){
			mvwprintw(my_win, row - 2, 0, "					");
			wmove(my_win, y, x);
			wrefresh(my_win);
			return;
		}

		wrefresh(my_win);
	}
}
