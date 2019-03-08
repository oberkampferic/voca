#ifndef FARBE_HPP
#define FARBE_HPP

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class farbe: public vector<float> {
  typename vector<float>::iterator it;
public:
  farbe();
  void print();
  void print(unsigned int index);
  float& operator [](int idx) {
    return vector<float>::data()[idx];
  }; 
};

class farbeTabelle: public vector<farbe> {
  typename vector<farbe>::iterator it;
public:
  farbeTabelle(int taille, unsigned int typeAlgo, float ratio);
  int print(void);
  farbe& operator [](int idx) {
    return vector<farbe>::data()[idx];
  }; 
};

#endif

