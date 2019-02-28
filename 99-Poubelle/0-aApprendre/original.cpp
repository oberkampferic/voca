#include <iostream>
#include <string>
#include <cstring>
#include <panel.h>

using namespace std;

#include "original.hpp"

int main() {
  PANEL  *my_panels[4];
  PANEL  *top;
  int ch;

  /* Initialize curses */
  initscr();
  //start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Initialize all the colors */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  windows * myWindows[4];
  myWindows[0] = new windows("truc0", COLOR_PAIR(1),  0, 0,40,20); myWindows[0]->show();
  myWindows[1] = new windows("truc1", COLOR_PAIR(2), 41, 0,40,20); myWindows[1]->show();
  myWindows[2] = new windows("truc2", COLOR_PAIR(3),  0,21,40,20); myWindows[2]->show();
  myWindows[3] = new windows("truc3", COLOR_PAIR(4), 41,21,40,20); myWindows[3]->show();
	  
  /* Attach a panel to each window */ 	/* Order is bottom up */
  for (int i=0; i<4; i++) my_panels[i] = new_panel(myWindows[i]->myWin);
	
  /* Set up the user pointers to the next panel */
  set_panel_userptr(my_panels[0], my_panels[1]);
  set_panel_userptr(my_panels[1], my_panels[2]);
  set_panel_userptr(my_panels[2], my_panels[3]);
  set_panel_userptr(my_panels[3], my_panels[0]);
	
  /* Update the stacking order. 2nd panel will be on top */
  update_panels();

  /* Show it on the screen */
  //attron(COLOR_PAIR(4));
  mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
  //attroff(COLOR_PAIR(4));
  doupdate();

  top = my_panels[3];
  while((ch = getch()) != KEY_F(1)) {
    switch(ch) {
    case 9:
      top = (PANEL *) panel_userptr(top);
      top_panel(top);
      break;
    }
    update_panels();
    doupdate();
  }
	
  endwin();
  return 0;
}

