#ifndef ORIGINAL2_HPP
#define ORIGINAL2_HPP

#include <iostream>
#include <string>
#include <cstring>

#include <curses.h>
#include <panel.h>
#include <form.h>

#define NLINES 20
#define NCOLS 40

using namespace std;

class windows{
  string label;
  chtype labelColor;
public:
  int startx, starty, height, width;
  WINDOW *myWin;

  void print_in_middle(int x, int y);
  int show();

  windows(string myLabel, chtype myLabelColor, int myStartx, int myStarty, int myWidth, int myHeight);
  ~windows();
};

#endif
