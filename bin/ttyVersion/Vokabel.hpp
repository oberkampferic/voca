#ifndef VOKABEL_HPP
#define VOKABEL_HPP

#include "main.hpp"
#include "../../lib/gründ/fichier.hpp"

//###########################################################

class triTable: public commun {
public:
  fichier str_rcdSET;
  TABLE_I lvl_rcdSET;
  TABLE_L tim_rcdSET;

  int fautIlRedemander(int pos, int index);
  int reussite(int pos, int index);
  int echec(int pos, int index);
  triTable(){};
};

//###########################################################

class Vokabel: public triTable {//: public table<string> {
private:
  int myRandom, sensQuestionnaire;
public:
  RECORD MonField;
  
  int result=-1;

  string reponse;

  void loadFile(string fileName);
  //--------------------------------------------------
  int Echec(string maReponse);
  int CBien();
  //--------------------------------------------------
  int NormalMode();
  //--------------------------------------------------
  int questionnaire();
  int isFullySetVector();
  int invite();
  //--------------------------------------------------
  int interrogation();
};

//###########################################################
#endif
