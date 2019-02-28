#ifndef RECORD_HPP
#define RECORD_HPP

#include "Field.hpp"
#include "../interfacetty/interfacetty.hpp"

template <typename T>
class record: virtual public interfacetty {
protected:

public:
  Field<T> myRecord[20];  
  int nbColonnes;

  void init();
  void init( T valeur);
  void set ( T valeur);  //Non testé
  int  isSet( T valeur); //Non testé
  int  setNbColonnes(int monNbColonnes) { nbColonnes=monNbColonnes; };
  int  store(string contenuFichier,
	     size_t *pos1, size_t *pos2,	    
	     int flagSuperStatic);
  int reste();
  int print();
  int printShort();
  int saveHumain(ostream * out);

  record();
  
  T& operator [](int idx) {
    return myRecord[idx].col;
  }

  T operator [](int idx) const{
    return myRecord[idx].get();
  }
};

#include "Record.tpp"

#endif
