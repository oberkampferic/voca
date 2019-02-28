#ifndef VOKABEL_HPP
#define VOKABEL_HPP
#include "../../lib/gründ/commun.hpp"
//#include <boost/algorithm/string.hpp>
#include "main.hpp"

#include "../../lib/gründ/fichier.hpp"

//Vokabel lit un fichier à la fois, le découpe,
// et l'ajoute ensuite dans l'un des Recordset appropriés.
// Chaque recordset gère lui même le nombre d'enregistrement et de colonnes qui le composent.
// Une fois que le fichier est intégré à un recordset, il peut être remplacé par un autre.
// Ainsi il est logique de n'avoir qu'une seule description de fichier pour Vokabel.

class triTable: public commun {
public:
  fichier stringR;
  lego< lego < int > > levelR;
  lego< lego < long> > timeR;

  int fautIlRedemander(int pos, int index);
  int reussite(int pos, int index);
  int echec(int pos, int index);
  triTable(){};
};

class triTableSingleton: public triTable {
public:
  triTableSingleton():triTable() {
    stringR.add((string) ""); //???
    levelR.add(0);
    timeR.add(0);
  };

  void setNbColonnes(int monNbColonnes){
//    stringR.monRecordSet[0].setNbColonnes(monNbColonnes);
//    levelR.monRecordSet[0].setNbColonnes(monNbColonnes);
//    timeR.monRecordSet[0].setNbColonnes(monNbColonnes);
  }
};

class Vokabel: public commun {//: public table<string> {
private:
  int myRandom, sensQuestionnaire;
public:

  triTableSingleton Erreur;
  triTableSingleton MonField;
  
  //  Field<string> * monField[4];
  RECORD monField; //A initialiser

  int result=-1;

int flagMemoHide=false, flagBlitz=false,
  saveFormat=false, flagSuperStatic=false, flagApprentissageMode=false, flagHasard=false;
  
  string reponse;

  int alteReponseIndex;
  int alteReponseSens;

  triTable maTriTable;
  triTable maTriTableNonSu;
  triTable maTriTableHauftig;
  triTable maTriTableDico;

  void loadFile(string fileName);

  //###########################################################
  int aideMenu();
  int menu();
  //###########################################################
  int Echec(string maReponse);
  int CBien();
  //###########################################################
//  int ShotMode();
//  int BlitzMode();
//  int HasardMode();
  int NormalMode();
  //###########################################################
  int questionnaire();
  int isFullySetVector();
  int invite();
  //###########################################################

  Vokabel(int argc, char *argv[]);
  ~Vokabel();

  int interrogation();
  int saveFile();  
};




#endif
