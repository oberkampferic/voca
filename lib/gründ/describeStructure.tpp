template <typename T>
void lego<T>::describeType() {
  T Eprouvette;
  INTERNET Internet;
  SGBD Sgbd;
  DATABASE Bdd;
  TABLE Tb;
  RECORD Rec;
  string maString;
  double monDouble;
  float monFloat;
  int monInt;
  long monLong;

  const type_info &tEprouvette=typeid(Eprouvette);
  const type_info &t0=typeid(Rec) ;
  const type_info &t1=typeid(Tb)  ;
  const type_info &t2=typeid(Bdd) ;
  const type_info &t3=typeid(Sgbd);
  const type_info &t4=typeid(Internet);
  const type_info &tstring=typeid(maString);
  const type_info &tfloat=typeid(monFloat);
  const type_info &tdouble=typeid(monDouble);
  const type_info &tint=typeid(monInt);
  const type_info &tlong=typeid(monLong);
  
  if      (tEprouvette==t0) cout << " type: RecordSet " ;
  else if (tEprouvette==t1) cout << " type: Table  " ;
  else if (tEprouvette==t2) cout << " type: Bdd " ;
  else if (tEprouvette==t3) cout << " type: Sgbd " ;
  else if (tEprouvette==t4) cout << " type: Internet " ;
  else if (tEprouvette==tstring) cout << " type: String " ;
  else if (tEprouvette==tfloat) cout << " type: Float " ;
  else if (tEprouvette==tint) cout << " type: Int " ;
  else if (tEprouvette==tdouble) cout << " type: Double " ;
  else cout << " type INCONNU!!!!!!!!!!!!!!!!!"; 
}

template <> inline
void lego<string>::describeStructure() {
  this->describeType();
  cout << this->size() << "éléments : ";
  for (int i=0; i<this->size(); i++)
    cout << vector<string>::data()[i] << "\t";
  cout << endl;
}

template <typename T>
void lego<T>::describeStructure() {
  this->describeType();
  cout << this->size() << "éléments " << endl;
  BOUCLE it->describeStructure();
}
