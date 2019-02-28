#include <iostream>
#include <string>
#include <cstring>
#include <panel.h>

using namespace std;

#include "original2.hpp"

int main() {
  PANEL  *my_panels[4];
  PANEL  *top;
  int ch;

  /* Initialize curses */
  initscr();
  start_color();
  cbreak();
  //  noecho();
  keypad(stdscr, TRUE);

  /* Initialize all the colors */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  windows * myWindows[4];
  myWindows[0] = new windows("Questionnaire", COLOR_PAIR(1),  0, 0,80,20); myWindows[0]->show();
  myWindows[1] = new windows("Options", COLOR_PAIR(2), 81, 0,80,20); myWindows[1]->show();
  myWindows[2] = new windows("Dictionnaire", COLOR_PAIR(3),  0,21,80,20); myWindows[2]->show();
  myWindows[3] = new windows("Fichiers connus", COLOR_PAIR(4), 81,21,80,20); myWindows[3]->show();
	  
  /* Attach a panel to each window */ 	/* Order is bottom up */
  for (int i=0; i<4; i++) my_panels[i] = new_panel(myWindows[i]->myWin);
	
  /* Set up the user pointers to the next panel */
  set_panel_userptr(my_panels[0], my_panels[1]);
  set_panel_userptr(my_panels[1], my_panels[2]);
  set_panel_userptr(my_panels[2], my_panels[3]);
  set_panel_userptr(my_panels[3], my_panels[0]);
	
  /* Show it on the screen */
  attron(COLOR_PAIR(4));
  mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
  attroff(COLOR_PAIR(4));

  /* Update the stacking order. 2nd panel will be on top */
  update_panels();
  doupdate();

  top = my_panels[3];
  char str[80];
  int p=0;
  while((ch = getch()) != KEY_F(1)) {
    switch(ch) {
    case 9:
      for (int i=0; i<4; i++) {
	top_panel( my_panels[i] );
	update_panels();
	doupdate();
      }
      top = (PANEL *) panel_userptr(top);
      top_panel(top);
      break;
    }

    //if (top==my_panels[0]) mvwprintw(myWindows[0]->myWin, 3, 2, "qmqslkdfj");
    //if (top==my_panels[0]) mvwprintw(myWindows[0]->myWin, 4, 2, "%d", p++);
    //waddstr(myWindows[0]->myWin, "gnia\n");
    //    mvwprintw(myWindows[0]->myWin, 8, 2, "");
    //waddstr(myWindows[0]->myWin, "gnia\n");
    //    cout << "gnia\n" << endl << endl;
    getstr(str);
    clear(); move(0,0);
      for (int i=0; i<4; i++) {
	top_panel( my_panels[i] );
	update_panels();
	doupdate();
      }
//    for (int i=0; i<4; i++) myWindows[i]->show();
//    update_panels();
//    doupdate();

    mvprintw(LINES - 2, 0, "You Entered: %s ", str);
    mvprintw(LINES - 1, 0, "Et maintenant?: ");
    refresh();
    update_panels();
    doupdate();
  }
	
  endwin();
  return 0;
}

