#include "main.hpp"
#include "pedagogie.hpp"
#include "Vokabel.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <panel.h>

#include <locale.h>
#include <iostream>
#include <curses.h>
#include <stdlib.h> //noetig fuer atexit()

using namespace std;

void quit() {
  //  for (int i=0; i<NBFENSTER; i++) delwin(myWindows[i]);
  //  endwin();
}

int main(int argc, char * argv[]) {
  //## INITIALISATION ###################################################
  //## Fenêtrage ####################
  setlocale(LC_ALL, "");

  initscr();
  atexit(quit);
  curs_set(0);
  //noecho();
  echo();
  curs_set(0);
  nocbreak();
  keypad(stdscr, 1);

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  init_pair(2, COLOR_BLUE, COLOR_WHITE);

  //## Voca ####################
  pedagogie maPedagogie(argc, argv);
  maPedagogie.saveFile();
  maPedagogie.Hauptmenu();

  return(0);
}
