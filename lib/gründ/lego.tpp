TEMPLATE__::add() { T monLego; this->push_back(monLego);}

INLINE____::add(string maChaine)   {  this->push_back(maChaine);}
TEMPLATE__::add(T monLego)         {  this->push_back(monLego); }

INLINE____::put()                  {  BOUCLE PRINT(*it);    CR; }
INLINE_I__::put()                  {  BOUCLE PRINT(*it);    CR; }
INLINE_L__::put()                  {  BOUCLE PRINT(*it);    CR; }
INLINE_F__::put()                  {  BOUCLE PRINT(*it);    CR; }
INLINE_D__::put()                  {  BOUCLE PRINT(*it);    CR; }
TEMPLATE__::put()                  {  BOUCLE it->put();     CR; }

INLINE____::print()                {  BOUCLE PRINT(*it);    CR; }
INLINE_I__::print()                {  BOUCLE PRINT(*it);    CR; }
INLINE_L__::print()                {  BOUCLE PRINT(*it);    CR; }
INLINE_F__::print()                {  BOUCLE PRINT(*it);    CR; }
INLINE_D__::print()                {  BOUCLE PRINT(*it);    CR; }
TEMPLATE__::print()                {  BOUCLE it->print();   CR; }

INLINE____::sort()                {  cout << "s" << endl; std::sort (this->begin(), this->end());}
INLINE_I__::sort()                {  cout << "i" << endl; std::sort (this->begin(), this->end());}
INLINE_L__::sort()                {  cout << "l" << endl; std::sort (this->begin(), this->end());}
INLINE_F__::sort()                {  cout << "f" << endl; std::sort (this->begin(), this->end());}
INLINE_D__::sort()                {  cout << "d" << endl; std::sort (this->begin(), this->end());}
TEMPLATE__::sort()                {  cout << "T" << endl; BOUCLE it->sort();}

INLINE____::saveHumain(ofstream * out)    {  BOUCLE SAVE(*it);     FR; }
INLINE_I__::saveHumain(ofstream * out)    {  BOUCLE SAVE(*it);     FR; }
INLINE_L__::saveHumain(ofstream * out)    {  BOUCLE SAVE(*it);     FR; }
INLINE_F__::saveHumain(ofstream * out)    {  BOUCLE SAVE(*it);     FR; }
INLINE_D__::saveHumain(ofstream * out)    {  BOUCLE SAVE(*it);     FR; }
TEMPLATE__::saveHumain(ofstream * out)    {  BOUCLE it->saveHumain(out); FR; }

template <typename T> int lego<T>::saveHumainDriver(string fileName){
  ofstream out(fileName);
  this->saveHumain(&out);
  out.close();
  return true;
}

//--------------------------------------------------

template <> inline void lego<string>::clean() {
  for (int i=0; i<this->size(); i++)
    if (vector<string>::data()[i].size()==0)
      this->erase(this->begin()+i);  
}

template <typename T> void lego<T>::clean() {
  for (it=this->begin(); it!=this->end(); ++it) it->clean();
  for (int i=0; i<this->size(); i++)
    if (vector<T>::data()[i].size()==0)
      this->erase(this->begin()+i);  
}

//--------------------------------------------------

TEMPLATE_I::loadBinaireDriver(string fileName) {
  int taille=this->size(); 
  for (int i=0; i<taille; i++)
    this->erase(this->begin());

  std::ifstream file(fileName, std::ios::binary);
  file.unsetf(std::ios::skipws);
  loadBinaire(&file);
  file.close();
}

//--------------------------------------------------

INLINE___I::loadBinaire(ifstream * in )     {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  //  string maLigne;
  for (int i=0; i<vectorSize; i++) {
    int maLength;
    in->read ((char *) &maLength, sizeof(int));
    char * memBlock;
    memBlock = new char [maLength+1];
    in->read (memBlock, maLength);
    memBlock[maLength]=0;
    string maLigne(memBlock);
    push_back(maLigne);
  }
  return true;
}

INLINE_I_I::loadBinaire(ifstream * in )     {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  int maVal;
  for (int i=0; i<vectorSize; i++) {
    in->read( (char *) &maVal, sizeof(int));
    push_back(maVal);
   };
  return true;
}

INLINE_L_I::loadBinaire(ifstream * in )     {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  long maVal;
  for (int i=0; i<vectorSize; i++) {
    in->read( (char *) &maVal, sizeof(long));
    push_back(maVal);
   };
  return true;
}

INLINE_F_I::loadBinaire(ifstream * in )     {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  float maVal;
  for (int i=0; i<vectorSize; i++) {
    in->read( (char *) &maVal, sizeof(float)); 
    push_back(maVal);
  };
  return true;
}

INLINE_D_I::loadBinaire(ifstream * in )     {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  double maVal;
  for (int i=0; i<vectorSize; i++) {
    in->read( (char *) &maVal, sizeof(double)); 
    push_back(maVal);
  };
  return true;
}

//--------------------------------------------------

TEMPLATE_I::loadBinaire(ifstream * in )    {
  unsigned int vectorSize;
  in->read((char *) &vectorSize, sizeof(unsigned int));
  for (int i=0; i < vectorSize; i++) {
    this->add();
    vector<T>::data()[i].loadBinaire(in);
  }
  return true;
}

//==================================================
TEMPLATE__::saveBinaireDriver(string fileName) {
  std::ofstream file(fileName, std::ios::binary);
  file.unsetf(std::ios::skipws);
  saveBinaire(&file);
  file.close();
}

//--------------------------------------------------

INLINE_I__::saveBinaire(ofstream * out )     {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  int maVal;
  BOUCLE {maVal=*it; out->write((char *) &maVal, sizeof(int));}
}

INLINE_L__::saveBinaire(ofstream * out )     {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  long maVal;
  BOUCLE {maVal=*it; out->write((char *) &maVal, sizeof(long));}
}

INLINE_F__::saveBinaire(ofstream * out )     {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  float maVal;
  BOUCLE {maVal=*it; out->write((char *) &maVal, sizeof(float));}
}

INLINE_D__::saveBinaire(ofstream * out )     {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  double maVal;
  BOUCLE {maVal=*it; out->write((char *) &maVal, sizeof(double));}
}

INLINE____::saveBinaire(ofstream * out )     {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  BOUCLE {
    unsigned int maLength;
    maLength=it->length();
    out->write((char *) &maLength, sizeof(unsigned int));
    *out << *it;
  }
}
//--------------------------------------------------
TEMPLATE__::saveBinaire(ofstream * out )    {
  unsigned int vectorSize = this->size();
  out->write((char *) &vectorSize, sizeof(unsigned int));
  BOUCLE it->saveBinaire(out);
}

