#include "Record.hpp"

//true:  pas de problème
//false: problème
//2:     on continue.

template <typename T>
void record<T>::init() {
  for (int i=0; i<nbColonnes; i++)
    record[i].init();
}

template <typename T>
void record<T>::init(T valeur){
  for (int i=0; i<nbColonnes; i++) {
    record[i].init(valeur);
  }
}

template <typename T>
int record<T>::store(string contenuFichier, size_t *pos1, size_t *pos2, int flagSuperStatic) {
  for (int i=0; i<nbColonnes; i++)
    switch (record[i].store(contenuFichier, pos1, pos2, flagSuperStatic)) {
    case true:  debug ("Record", "store", "Fin    point 1\n")              ; return true;
    case false: debug ("Record", "store", "Erreur point 2\n")              ; return false;
    case 2:     /*debug ("Record", "store", "Pas de problème, on continue.B");*/  break;
    }
  return 2;
}

template <typename T>
int record<T>::reste() {
  if ((record[0].level==0) || (record[1].level==0)) {
    for (int i=0; i<nbColonnes; i++) 
      record[i].saveShort(&cout);
    cout << endl;
  }
}

template <typename T>
int record<T>::print() {
  saveHumain(&cout);
}

template <typename T>
int record<T>::printShort() {
  for (int i=0; i<nbColonnes; i++) record[i].saveShort(&cout);
  cout << endl;
}

template <typename T>
int record<T>::saveHumain(ostream * out) {
  for (int i=0; i<nbColonnes; i++) record[i].saveHumain(out);
  *out << endl;
}

template <> inline
Record<string>::Record() {
  for (int i=0; i<20; i++)
    record[i].col="#";
}

template <> inline
Record<int>::Record() {
  for (int i=0; i<20; i++)
    record[i].col=0;
}

template <> inline
Record<long>::Record() {
  for (int i=0; i<20; i++)
    record[i].col=0;
}
