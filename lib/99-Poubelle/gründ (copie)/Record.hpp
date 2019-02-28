#ifndef RECORD_HPP
#define RECORD_HPP

//#include "../../main.hpp"
#include "Field.hpp"
#include "commun.hpp"
#include "../interfacetty/interfacetty.hpp"

template <typename T>
class record: virtual public commun {
public:

  Field<T> record[20];
  int nbColonnes;

  void init();
  void init( T valeur);

  int setNbColonnes(int monNbColonnes) { nbColonnes=monNbColonnes; };
  int store(string contenuFichier,
	    size_t *pos1, size_t *pos2,	    
	    int flagSuperStatic);
  int reste();
  int print();
  int printShort();
  int saveHumain(ostream * out);


    record();
  
    T& operator [](int idx) {
        return record[idx].col;
    }
//  T& operator []( int idx) {
//        return record[idx];
//    }

    T operator [](int idx) const {
        return record[idx].col;
    }
};

#include "Record.tpp"

#endif
