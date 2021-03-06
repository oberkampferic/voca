#ifndef TABLE_HPP
#define TABLE_HPP

//#include "fichier.hpp"

#include "Head.hpp"
#include "recordSet.hpp"

template <typename T>
class table: public head, public recordSet<T> {

  // public RECORD {


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
