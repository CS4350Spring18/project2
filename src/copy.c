#include "copy.c"

int copy(WINDOW* my_win,int &length, struct Page* page){
	char *myString[length+1];

	int key;
	int y,x;
	int row,col;
	

	getyx(my_win,y,x);
	getmaxyx(my_win,row,col);

	//Checks bounds ---needs eyes---
	while(length > x || col)
		length = length-1;

	//reads actual line with input length into myString
	winnstr(WINDOW *my_win, *myString, length);

	return myString;
}

void paste(WINDOW* my_win, char &myString, struct Page* page){
	int key;
	int y,x;
	int row,col;

	getyx(my_win,y,x);
	getmaxyx(my_win,row,col);

	while( myString = getch()){
		if ( x > page->sizes[y]){
			wmove(my_win,y,x+1);
		}
		else{
			wmove(my_win,y+1,x);
		}
	}
}
