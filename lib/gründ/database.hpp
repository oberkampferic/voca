#include <iostream>
#include <fstream>
#include <string>
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
//############################################################
//############################################################
//############################################################
//############################################################
//############################################################
//############################################################

template <typename T> 
class lego: public vector<T> {
private:
  typename vector<T>::iterator it;
public:
  void print();
  void saveHumain(ostream * out);
  //  void import(ifstream * in);
  void put();

  lego(){};
  lego(T val){ this->push_back(val); };
   ~lego(){};

  T& operator [](int idx) {
    return vector<T>::data()[idx];
  }
};

TEMPLATE::storage (string & contenuFichier) {
  cout << "Storage=========================================\n";

  size_t pos1=0, pos2;
  RECORD monRecord;
  //  record<string> monRecord; monRecord.setNbColonnes(nbColonnes);
  string str;
  int x=0; 

  cout << contenuFichier << endl;

  for(;;) {
    flagCount++; /* on est arrivé là */
    switch (monRecord.store(contenuFichier, &pos1, &pos2)) {
    case true:  cout << "Fin de boucle.\n";
      if (flagCount==-1) flagCount = x;        return true;
    case false: cout << "Erreur innatendue."; return false;
    case 2:     cout << "      on continue."; break;
    }
    this->push_back(monRecord);
    x++; 
  }
  cout << endl;
  cout << "Erreur fin de boucle.";
};

TEMPLATE::store(string contenuFichier, size_t *pos1, size_t *pos2, RECORD monRecord ) {
  for (int i=0; i<nbColonnes; i++)
    switch (this->store(contenuFichier, pos1, pos2)) {
    case true:  cout << "Fin    point 1\n"    ; return true;
    case false: cout << "Erreur point 2\n"    ; return false;
    case 2:     cout << "On continue.  \n"    ; break;
    }
  return 2;
}

  INLINE__::storeField (string contenuFichier, size_t *pos1, size_t *pos2, RECORD monRecord ) {
  *pos2 = contenuFichier.find("|", *pos1);
  
  if (*pos2==contenuFichier.npos) return true;
  col = contenuFichier.substr(*pos1, (*pos2-*pos1));
  *pos1 = *pos2+1;

  return 2;
}


//############################################################
//############################################################
//############################################################


INLINE__::put()                  {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::put()                  {  BOUCLE it->put();     CR; }
		                 
INLINE__::print()                {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::print()                {  BOUCLE it->print();   CR; }

INLINE__::saveHumain(ostream * out)    {  BOUCLE SAVE(*it);     FR; }
TEMPLATE::saveHumain(ostream * out)    {  BOUCLE it->saveHumain(out); FR; }

//INLINE__::import(ostream *  in)    {  BOUCLE LOAD(*it);     FR; }
//TEMPLATE::import(ostream *  in)    {  BOUCLE it->import( in); FR; }

INLINE__::storage(string & contenuFichier) {
}












//Poubelle:
//for (int i=0; i<vector<T>::size(); i++)
//  vector<T>::data()[i].print();  
//for (int i=0; i < vector<string>::size(); i++)
//  cout << vector<string>::data()[i] << "|";

