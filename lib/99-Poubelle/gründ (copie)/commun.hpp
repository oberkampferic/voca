#ifndef COMMUN_HPP
#define COMMUN_HPP

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
#include <panel.h>

#include "../interfacetty/interfacetty.hpp"

#include <panel.h>
#include <form.h>

#include "../interfacetty/interfacetty.hpp"

using namespace std;

class commun: virtual public interfacetty {
  //class commun: public parser {
public:
  //autres haut niveau
  void bascule (int *flag);
  int  isSetVector(vector<int> coli);
  long monTemps();
};

#endif
