INLINE__::put()                  {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::put()                  {  BOUCLE it->put();     CR; }

INLINE__::add(string maChaine)   {  this->push_back(maChaine);}
TEMPLATE::add(T monLego)         {  this->push_back(monLego); }
		                 
INLINE__::print()                {  BOUCLE PRINT(*it);    CR; }
TEMPLATE::print()                {  BOUCLE it->print();   CR; }

INLINE__::saveHumain(ostream * out)    {  BOUCLE SAVE(*it);     FR; }
TEMPLATE::saveHumain(ostream * out)    {  BOUCLE it->saveHumain(out); FR; }

//INLINE__::import(ostream *  in)    {  BOUCLE LOAD(*it);     FR; }
//TEMPLATE::import(ostream *  in)    {  BOUCLE it->import( in); FR; }

//INLINE__::storage(string & contenuFichier) {
//}

//Poubelle:
//for (int i=[X]; i<vector<T>::size(); i++)
//  vector<T>::data()[i].print();  
//for (int i=[X]; i < vector<string>::size(); i++)
//  cout << vector<string>::data()[i] << "|";

