template <typename T> int lego<T>::loadHumainDriver(string fileName){
  ifstream in(fileName);
  loadHumain(&in);  
  in.close();
  return true;
}

template <> inline int lego<string>::loadHumainSubLoad (string * strMotif) {
  size_t pos1=0, pos2=0;
  string col;
  int flagLast=false;

  for (;;) {
    pos2 = strMotif->find("|", pos1);

    if (pos2==string::npos) {
      flagLast=true;
      pos2=strMotif->size();
    }

    col = strMotif->substr(pos1, (pos2-pos1));
    push_back(col);
    
    pos1 = pos2+1;

    if (flagLast) return true;
  }
}

template <> inline int lego<string>::loadHumain(ifstream * in) {
  string maLigne;
  getline(*in, maLigne);
  if (maLigne[0]==0) return 0;
  loadHumainSubLoad (&maLigne);
  this->erase(this->end());
  return 1;
}

template <typename T> int lego<T>::loadHumain(ifstream * in) {
  int compteur=0;
  do {
    this->add();
    if ((vector<T>::data()[this->size()-1].loadHumain(in))==0) {
      this->erase(this->end());
      return compteur;
    }
    compteur++;
  } while (true);
}


