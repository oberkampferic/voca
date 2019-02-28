// #include <ncurses.h>
// 
// // int main()
// // {	
// // 	initscr();			/* Start curses mode 		  */
// // 	printw("Hello World !!!");	/* Print Hello World		  */
// // 	refresh();			/* Print it on to the real screen */
// // 	getch();			/* Wait for user input */
// // 	endwin();			/* End curses mode		  */
// // 
// // 	return 0;
// // }
// 
// 
// int main()
// {
//   int ch;
//   int boldFlag=true;
// 
//   initscr();			/* Start curses mode 		*/
//   raw();				/* Line buffering disabled	*/
//   keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
//   noecho();			/* Don't echo() while we do getch */
// 
//   printw("Type any character to see it in bold\n");
//   for(;;) {
//     ch = getch();			/* If raw() hadn't been called
// 					 * we have to press enter before it
// 					 * gets to the program 		*/
//     if(ch == KEY_F(1))		/* Without keypad enabled this will */
//       if (boldFlag) boldFlag=false; else boldFlag=true;
// 	//printw("F1 Key pressed");/*  not get to us either	*/
//     /* Without noecho() some ugly escape
//      * charachters might have been printed
//      * on screen			*/
//     else
//       if (boldFlag) {
// 	attron(A_BOLD); printw("%c", ch); attroff(A_BOLD);
//       } else            printw("%c", ch);
//     
//     refresh();			/* Print it on to the real screen */
//   }
// 
//   getch();			/* Wait for user input */
//   endwin();			/* End curses mode		  */
// 
//   return 0;
// }

#include <cstring>
#include <panel.h>
#include <iostream>
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
#define NLINES 20
#define NCOLS 80

using namespace std;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

typedef struct _PANEL_DATA {
  int hide;	/* TRUE if panel is hidden */
}PANEL_DATA;

#define NLINES 20
#define NCOLS 80

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main() {
//  windows myWindow1("main", COLOR_GREEN, 1, 1, 10, 8);
//  myWindow1.show();
  
  WINDOW *my_wins[3];
  PANEL  *my_panels[4];
  PANEL_DATA panel_datas[4];
  PANEL_DATA *temp;
  int ch;

  /* Initialize curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Initialize all the colors */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  init_wins(my_wins, 3);

  /* Attach a panel to each window */ 	/* Order is bottom up */
  my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
  my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
  my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */
  //  my_panels[3] = new_panel(myWindow1.myWin);
  
  /* Initialize panel datas saying that nothing is hidden */
  panel_datas[0].hide = FALSE;
  panel_datas[1].hide = FALSE;
  panel_datas[2].hide = FALSE;
  //  panel_datas[3].hide = FALSE;
  
  set_panel_userptr(my_panels[0], &panel_datas[0]);
  set_panel_userptr(my_panels[1], &panel_datas[1]);
  set_panel_userptr(my_panels[2], &panel_datas[2]);
  //  set_panel_userptr(my_panels[3], &panel_datas[3]);

  /* Update the stacking order. 2nd panel will be on top */
  update_panels();

  /* Show it on the screen */
  attron(COLOR_PAIR(4));
  mvprintw(LINES - 3, 0, "Show or Hide windows: 'a'(1st window)  'b'(2nd Window)  'c'(3rd Window)");
  mvprintw(LINES - 2, 0, "F1 to Exit");

  attroff(COLOR_PAIR(4));
  doupdate();


  while((ch = getch()) != KEY_F(1)) {
//    cout << "gnia" << endl;
//
//    temp = (PANEL_DATA *)panel_userptr(my_panels[3]);
//    show_panel(my_panels[3]);
//    temp->hide = FALSE;
//    cout << "gnia" << endl;
  
    switch(ch) {
    case 'a':			
      temp = (PANEL_DATA *)panel_userptr(my_panels[0]);
      if(temp->hide == FALSE) {
	hide_panel(my_panels[0]);
	temp->hide = TRUE;
      } else {
	show_panel(my_panels[0]);
	temp->hide = FALSE;
      } break;
    case 'b':
      temp = (PANEL_DATA *)panel_userptr(my_panels[1]);
      if(temp->hide == FALSE) {
	hide_panel(my_panels[1]);
	temp->hide = TRUE;
      } else {
	show_panel(my_panels[1]);
	temp->hide = FALSE;
      } break;
    case 'c':
      temp = (PANEL_DATA *)panel_userptr(my_panels[2]);
      if(temp->hide == FALSE) {
	hide_panel(my_panels[2]);
	temp->hide = TRUE;
      } else {
	show_panel(my_panels[2]);
	temp->hide = FALSE;
      } break;
    }
    myWindow1.show();
    update_panels();
    doupdate();
  }
  endwin();
  return 0;
}

/* Put all the windows */
void init_wins(WINDOW **wins, int n)
{
  int x, y, i;
  char label[80];

  y = 2; x = 10;
  for(i = 0; i < n; ++i) {
    wins[i] = newwin(NLINES, NCOLS, y, x);
    sprintf(label, "Window Number %d", i + 1);
    win_show(wins[i], label, i + 1);
    y += 3; x += 7;
  }
}


/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color) {
  int startx, starty, height, width;

  getbegyx(win, starty, startx);
  getmaxyx(win, height, width);

  box(win, 0, 0);
  mvwaddch(win, 2, 0, ACS_LTEE); 
  mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
  mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
  print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {	int length, x, y;
  float temp;

  if(win == NULL)    win = stdscr;  getyx(win, y, x);
  if(startx != 0)    x = startx;
  if(starty != 0)    y = starty;
  if(width == 0)     width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = startx + (int)temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, color);
  refresh();
}
