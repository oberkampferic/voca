#ifndef RECORDSET_HPP
#define RECORDSET_HPP

#include <boost/algorithm/string.hpp>
#include "Record.hpp"
#include "Head.hpp"

template<typename T>
class recordSet: public commun, public vector< record<T> > {
public:
  int nbColonnes=0;
  int flagCount=-1;
  int flagSuperStatic=false;
  
  vector< record<T> > monRecordSet;
  void set(T valeur);
  int swap(int index1, int index2);
  int sort(int critere);
  //#########################################
  //search:     recherche du motif au début des mots
  //searchInv:  recherche du motif à partir de la fin des mots
  //searchIn:   recherche du motif dans le mots
  int search          (int critere, int critere2, string motif);
  int searchInv       (int critere, int critere2, string motif);
  int searchIn        (int critere, int critere2, string motif);
  //#########################################
  int print();
  int printShort();
  int printAllShort();
  int printAll();
  int reste();
  //#########################################
  int reset();
  int import(ifstream &in);                  //quel sens?
  void addVoid();
  int storage(string &contenuFichier);     //prends une chaine déjà formaté et l'ajoute
  int saveHumain(ofstream &out);

  T& operator() (int x, int y) {
    return monRecordSet[x].myRecord[y].col;
  }
};

#include "recordSet.tpp"

#endif
