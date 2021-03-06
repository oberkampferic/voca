#ifndef LEGO_HPP
#define LEGO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <typeinfo>
#include "Head.hpp"

// pour les templates sans valeurs de retour
#define INLINE____   template <> inline void lego<string>
#define INLINE_I__   template <> inline void lego<int>
#define INLINE_L__   template <> inline void lego<long>
#define INLINE_F__   template <> inline void lego<float>
#define INLINE_D__   template <> inline void lego<double>
#define TEMPLATE__   template <typename T> void lego<T>

// pour les templates avec un code erreur en retour
#define INLINE___I   template <> inline int  lego<string>
#define INLINE_I_I   template <> inline int  lego<int>
#define INLINE_L_I   template <> inline int  lego<long>
#define INLINE_F_I   template <> inline int  lego<float>
#define INLINE_D_I   template <> inline int  lego<double>
#define TEMPLATE_I   template <typename T> int  lego<T>

#define INTERNET   lego<lego<lego<lego<lego<string> > > > >
#define SGBD       lego<lego<lego<lego<string> > > >
#define DATABASE   lego<lego<lego<string> > >
#define DATABASE_I lego<lego<lego<int> > >
#define DATABASE_L lego<lego<lego<long> > >
#define DATABASE_F lego<lego<lego<float> > >
#define DATABASE_D lego<lego<lego<double> > >
#define TABLE      lego<lego<string> >
#define TABLE_I    lego<lego<int> >
#define TABLE_L    lego<lego<long> >
#define TABLE_F    lego<lego<float> >
#define TABLE_D    lego<lego<double> >
#define RECORD     lego<string >
#define RECORD_I   lego<int >
#define RECORD_L   lego<long >
#define RECORD_F   lego<float >
#define RECORD_D   lego<double >

#define BOUCLE  for (it=this->begin(); it!=this->end(); ++it)
#define CR            cout << endl
#define FR            *out << endl

#define PUT(X)        cout << X
#define PRINT(X)      cout << X << "\t"
#define SAVE(X)       *out << X << "|"
#define LOAD(X)       *in  >> X //>> "|"
#define SAVEEXPE2(X)  *out << X << "\n"
//#define LOADEXPE2(X)  

using namespace std;
//#################################################

template <typename T> 
class lego: public vector<T>, public head {
private:
  typename vector<T>::iterator it;
public:
  void add();
  void add(T val);
  void put();
  void print();
  void sort();
  //----------------------------------------
  void describeStructure();
  void describeType();
  //----------------------------------------
  int importDriver(string fileName); 
  int import(ifstream * in, string * maLigne);
  //----------------------------------------
  void saveBinaireDriver(string fileName);
  void saveBinaire(ofstream * out);
  int  loadBinaireDriver(string fileName);
  int  loadBinaire(ifstream * in);
  //----------------------------------------
  int  loadHumainDriver(string fileName); 
  int  loadHumain(ifstream * in);
  int  loadHumainSubLoad (string * strMotif);
  int  saveHumainDriver(string fileName);
  void saveHumain(ofstream * out);
  //----------------------------------------
  void clean();
  //----------------------------------------
  lego(){};
  lego(T val){ this->push_back(val); };
   ~lego(){};

  T& operator [](int idx) {
    return vector<T>::data()[idx];
  }
};

//##########################################
#include "lego.tpp"
#include "legoLoad.tpp"
#include "legoImport.tpp"
#include "describeStructure.tpp"

#endif

