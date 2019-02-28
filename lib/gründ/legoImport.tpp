//template <> inline int DATABASE::importDriver(string fileName){
//  ifstream in(fileName);
//  string maLigne;
//  
//  while (getline (in, maLigne)) {
//    if (maLigne[0]==0) {
//      //cout << "fin detecté" << endl;
//      return true;
//    } else {
//      this->add();
//      this->back().import(&in, &maLigne);
//    }
//  }
//  in.close();
//  return true;
//}
//
template <> inline int TABLE::importDriver(string fileName){
  ifstream in(fileName);
  string maLigne;
  
  while (getline (in, maLigne))
    if (maLigne[0]==0)
      return true;
    else 
      import(&in, &maLigne);
  
  in.close();
  return true;
}

template <typename T> int lego<T>::import(ifstream * in, string * maLigne) {
  RECORD monRecord;
  preParsing(maLigne);  //découpage de la ligne

  size_t pos1=0, pos2=0;
  string col;

  int valRet=10;
  
  for (;;) {
    pos2 = maLigne->find("|", pos1);

    if (pos2==string::npos){
      pos2=maLigne->size();
      valRet=false; //là c la fin
    }

    col = maLigne->substr(pos1, (pos2-pos1));
    monRecord.push_back(col);
    pos1 = pos2+1;

    if (valRet!=10){
      if((monRecord.size()!=0))
	this->push_back(monRecord);
      return valRet;
    }
  }
}
