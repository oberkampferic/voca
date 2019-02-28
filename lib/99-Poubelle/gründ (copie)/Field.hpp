#ifndef FIELD_HPP
#define FIELD_HPP

#include "commun.hpp"

template <typename T>
class Field: virtual public commun {
public:
  T col;

  void init();
  void init(T valeur);
  Field();

  
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
