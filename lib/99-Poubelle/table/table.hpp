#ifndef PREVOKABEL
#define PREVOKABEL

#include "../gründ/recordSet.hpp"

template <typename T>
class table: public head, public recordSet<T> {
public:
  string fileName;
  int flagMemo=false, flagShot=false;

  string contenuFichier;
  
  void importTable(string fileName);
  int loadFile(string fileName);
  int parsing();
};

#include "table.tpp"

#endif
 
