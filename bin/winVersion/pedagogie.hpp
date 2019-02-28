#ifndef PEDAGOGIE_HPP
#define PEDAGOGIE_HPP

#include <cstring>
#include <panel.h>


#include "main.hpp"
#include "Vokabel.hpp"
#include "../../lib/winRoutines/winRoutines.hpp"

class pedagogie: public Vokabel{
private:
  int Hauptantwort;
public:
  void fileAppendToRecordSet(string fileName);
  int Hauptmenu(char Hauptantwort);
  int Hauptmenu();
  pedagogie(int argc, char *argv[]);
  ~pedagogie();
};

#endif
