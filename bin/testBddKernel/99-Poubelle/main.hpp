#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../lib/gründ/preParser.hpp"

#define TEMPLATE   template <typename T> void lego<T>
#define IN__LINE   template <> inline void lego<string>

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

//############################################################

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
//############################################################

IN__LINE::put()                  {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::put()                  {  BOUCLE it->put();     CR; }

IN__LINE::add(string maChaine)   {  this->push_back(maChaine);}
TEMPLATE::add(T monLego)         {  this->push_back(monLego); }
		                 
IN__LINE::print()                {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::print()                {  BOUCLE it->print();   CR; }

IN__LINE::saveHumain(ostream * out)    {  BOUCLE SAVE(*it);     FR; }
TEMPLATE::saveHumain(ostream * out)    {  BOUCLE it->saveHumain(out); FR; }

//IN__LINE::import(ostream *  in)    {  BOUCLE LOAD(*it);     FR; }
//TEMPLATE::import(ostream *  in)    {  BOUCLE it->import( in); FR; }

//IN__LINE::storage(string & contenuFichier) {
//}












//Poubelle:
//for (int i=0; i<vector<T>::size(); i++)
//  vector<T>::data()[i].print();  
//for (int i=0; i < vector<string>::size(); i++)
//  cout << vector<string>::data()[i] << "|";

