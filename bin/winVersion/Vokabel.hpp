#ifndef VOKABEL_HPP
#define VOKABEL_HPP
#include <boost/algorithm/string.hpp>
#include "main.hpp"
#include "../../lib/gründ/Record.hpp"
#include "../../lib/gründ/Head.hpp"
#include "../../lib/gründ/commun.hpp"
#include "panel.h"

#include "../../lib/winRoutines/winRoutines.hpp"
#include "../../lib/gründ/preParser.hpppp"
#include "../../lib/interfacetty/interfacetty.hpp"

using namespace std;

class Vokabel: public descriptionFichier, public couleurWindows {
private:
  int myRandom, sensQuestionnaire;
public:
  
  record Erreur;
  Field * monField[4];
  //  int result;


  int result=-1;
  int flagCountHauftig=-1;
  int flagCountDico=-1;
  int flagCount=-1, flagMemo=false, flagMemoHide=false, flagShot=false, flagBlitz=false,
    saveFormat=false, flagSuperStatic=false, flagApprentissageMode=false, flagHasard=false;
  
  string contenuFichier;
  string reponse;

  int alteReponseIndex;
  int alteReponseSens;
  
  vector<Record> recordSet;
  vector<Record> recordSetNonSu;
  vector<Record> recordSetHauftig;
  vector<Record> recordSetDico;
  
  string fileName;

  int swap(int index1, int index2);
  int sort(int critere);

  int searchGen(vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int search(int critere, int critere2, string motif);
  int searchHauftig(int critere, int critere2, string motif);
  int searchDico(int critere, int critere2, string motif);

  int searchInvGen(vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int searchInv(int critere, int critere2, string motif);
  int searchInvHauftig(int critere, int critere2, string motif);
  int searchInvDico(int critere, int critere2, string motif);

  int searchInGen(vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int searchIn(int critere, int critere2, string motif);
  int searchInHauftig(int critere, int critere2, string motif);
  int searchInDico(int critere, int critere2, string motif);
  
  int loadFile(string fileName);
  int parsing();
  int storage();
  int storageHauftigste();
  int storageDico();
  int reset();
  int printAll();
  int printShort();
  int printAllShort();
  int print();
  int printErreur();
  int reste();
  int aideMenu();
  int menu();

  int Echec(string maReponse);
  int CBien();
  
  int ShotMode();
  int BlitzMode();
  int HasardMode();
  int NormalMode();
  
  int questionnaire();
  int isFullySetVector();
  int invite();  
public:
  Vokabel(int argc, char *argv[]);
  ~Vokabel();

  int interrogation();
  int saveFile();  
};




#endif
