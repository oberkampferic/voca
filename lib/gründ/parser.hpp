#ifndef PARSER
#define PARSER


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

//#include "../interfacetty/interfacetty.hpp"

//class parser: private interfacetty {

using namespace std;

class parser {
public:
  int  ReplaceString(string * subject, string search, string strReplace);
  int  nbSeparateurEnLigne(string * ligne);
  int  nbColonneEnLigne(string * ligne);

  //partie entete
  int  detectNbColonne(string * contenuFichier);
  int  detectNbColonneInit(string * contenuFichier);
};

#endif 
