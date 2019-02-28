#ifndef BERGSON_HPP
#define BERGSON_HPP

#include "openGl.hpp"

class bergson:public openGlInterface{
public:
  int flagShot=false, flagBlitz=true;

  static tableBergson maTableVide;
  static string s_Categorie;
  static string s_Name;
  static string s_Date1;
  static string s_Date2;
  static string s_Memo;
  
  void static afficherListeDessin1();
  void static afficherListeDessin2();
  void static afficherListeTexte();
  void static afficherListe();
  
  void static interrogation();

  void static my_handle_key(unsigned char key, int x, int y);

  int static loadMetaData();
  int static saveMetaData();
  bergson(int argc, char * argv[]);
  
};

#endif
