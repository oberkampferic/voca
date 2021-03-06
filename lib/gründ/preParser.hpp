#ifndef PREPARSER
#define PREPARSER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

#include "commun.hpp"
#include "parser.hpp"

using namespace std;

class preParser: virtual public commun, public parser {
public:
  void preParsing(string * contenuFichier);
  int  postParsing(string * contenuFichier);
  int  deleteStrangeCharacters(string * contenuFichier);
  int  deleteNumbers(string * contenuFichier);
  int  controleCoherenceFichier(string * contenuFichier, unsigned int nbColonne);

};

#endif
