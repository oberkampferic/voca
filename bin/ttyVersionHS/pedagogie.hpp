#ifndef PEDAGOGIE_HPP
#define PEDAGOGIE_HPP

#include "main.hpp"
#include "Vokabel.hpp"

class pedagogie: public Vokabel{
private:
  int Hauptantwort;
public:
  int Hauptmenu();
  pedagogie(int argc, char *argv[]);
  ~pedagogie();
};

#endif
