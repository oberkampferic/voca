#include <iostream>
#include <string>
#include <cstring>
#include <panel.h>

#define NLINES 10
#define NCOLS 40


class windows{
  string label;
  chtype labelColor;
public:

  int startx, starty, height, width;
  
  WINDOW *myWin;
  void print_in_middle(int x, int y) {
    int length;
    float temp;

    if(myWin == NULL)    myWin = stdscr;  getyx(myWin, y, x);
    if(startx != 0)    x = startx;
    if(starty != 0)    y = starty;
    if(width == 0)     width = 80;

    length = label.size();
    temp = (width - length)/ 2;
    x = startx + (int)temp;
    //    wattron(myWin, labelColor);
    mvwprintw(myWin, y, x, "%s", label.c_str());
    //    wattroff(myWin, labelColor);
    refresh();
  }

  int show() {
    myWin = newwin(height, width, starty, startx);
    getbegyx(myWin, starty, startx);
    getmaxyx(myWin, height, width);
    box(myWin, 0, 0);
    mvwaddch(myWin, 2, 0, ACS_LTEE); 
    mvwhline(myWin, 2, 1, ACS_HLINE, width - 2); 
    mvwaddch(myWin, 2, width - 1, ACS_RTEE); 
    print_in_middle(0, 1);
  };

  windows(string myLabel, chtype myLabelColor, int myStartx, int myStarty, int myWidth, int myHeight) {
    label=myLabel;
    labelColor=myLabelColor;
    startx=myStartx;
    starty=myStarty;
    height=myHeight;
    width=myWidth;
    
    myWin = newwin(NLINES, NCOLS, starty, startx);
    
    show();
  }
  
  ~windows(){};
};
