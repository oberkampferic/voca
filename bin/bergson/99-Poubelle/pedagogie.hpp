#ifndef PEDAGOGIE_HPP
#define PEDAGOGIE_HPP

#include "main.hpp"
#include "bergson.hpp"

class pedagogie: public bergson{
private:
  int Hauptantwort;
public:
  int Hauptmenu();
  pedagogie(int argc, char * argv[]):bergson(argc, argv){};
};

#endif
