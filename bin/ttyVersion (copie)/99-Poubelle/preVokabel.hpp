#ifndef PREVOKABEL
#define PREVOKABEL

#include "../../lib/gründ/recordSet.hpp"

class table: public head{
public:
  int flagMemo=false, flagShot=false;

  string fileName;
  string contenuFichier;
  
  void pedagogieLoadFile(string fileName, recordSet<string> * myRecordSet);

  int loadFile(string fileName);
  int parsing();


};

#endif
