#ifndef WIN_ROUTINES_HPP
#define WIN_ROUTINES_HPP

#include <iostream>
#include <form.h>
#include <panel.h>

//#include "lib/gründ/commun.hpp"

#define NBFENSTER 3

class couleurWindows {
public:
  char str[80]="";
  WINDOW * myWindows[4];

  FORM * guiForm;
  FIELD **guiField;

  void mesCouleursWindows(void){
  for (int i=0; i<NBFENSTER; i++) box (myWindows[i],0,0);
  bkgd(COLOR_PAIR(1));
  wbkgd(stdscr, COLOR_PAIR(2));
  for (int i=0; i<NBFENSTER; i++) wbkgd(myWindows[i], COLOR_PAIR(2));
}

void mesCouleursWindows2(void){
  refresh();
  for (int i=0; i<NBFENSTER; i++) wrefresh(myWindows[i]);
  for (int i=0; i<NBFENSTER; i++) wnoutrefresh(myWindows[i]);
  doupdate();
}
  
  //void mesCouleursWindows(void);
  //void mesCouleursWindows2(void);
};

#endif
 
