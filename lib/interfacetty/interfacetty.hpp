#ifndef INTERFACETTY
#define INTERFACETTY

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class interfacetty{
public:
  int flagVerbose=false;
  
  void kurz(string message);
  void message(string classe, string fonction, string message);
  void debug (string classe, string fonction, string message);
  void erreur (string classe, string fonction, string message);
  void erreur (string classe, string fonction, char** message);
};

#endif
