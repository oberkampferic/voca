#ifndef FIELD_HPP
#define FIELD_HPP


#include "../interfacetty/interfacetty.hpp"

template <typename T>
class Field: virtual public interfacetty {
public:
  T col;

  Field();
  Field(T valeur);
  
  void init();
  void init (T valeur);
  void set  (T valeur);//Non testé
  T    get  ();        //Non testé
  int  isSet(T valeur);//Non testé

  
  int store(string contenuFichier,
	    size_t *pos1, size_t *pos2,
	    int flagSuperStatic);
  int reset();
  int print();
  int saveHumain(ostream * out);
  int saveShort(ostream * out);
};

#include "Field.tpp"

#endif
