#ifndef LEGO_HPP
#define LEGO_HPP

#include <iostream>
#include <fstream>
#include <vector>

#define TEMPLATE   template <typename T> void lego<T>
#define INLINE__   template <> inline void lego<string>

#define DATABASE   lego<lego<lego<string> > >
#define TABLE      lego<lego<string> >
#define RECORD     lego<string >
#define BOUCLE     for (it=this->begin(); it!=this->end(); ++it)
#define CR         cout << endl
#define FR         *out << endl
#define PUT(X)     cout << X
#define PRINT(X)   cout << X << "\t"
#define SAVE(X)    *out << X << "|"
#define LOAD(X)    *in  >> X >> "|"

using namespace std;

//#################################################

template <typename T> 
class lego: public vector<T> {
private:
  typename vector<T>::iterator it;
public:
  void print();
  void saveHumain(ostream * out);
  //  void import(ifstream * in);
  void add(T val);
  void put();

  lego(){};
  lego(T val){ this->push_back(val); };
   ~lego(){};

  T& operator [](int idx) {
    return vector<T>::data()[idx];
  }
};
//#################################################

#include "lego.tpp"

#endif

