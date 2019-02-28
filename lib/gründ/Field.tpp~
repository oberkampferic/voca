#ifndef FIELDTPP
#define FIELDTPP

template <> inline void Field<string>::init(){  col= "#"; }
template <> inline void Field<int>::init()   {  col= 0;   }
template <> inline void Field<long>::init()  {  col= 0;   }

//--------------------------------------------------

template <typename T>
void Field<T>::init(T valeur){
  col=valeur;
}
  
template <> inline Field<string>::Field()    {  col= "#"; }
template <> inline Field<int>::Field()       {  col= 0;   }
template <> inline Field<long>::Field()      {  col= 0;   }

//--------------------------------------------------

/* ????
  trois issue:
  fin là où l'on attendait        true
  fin là où l'on l'attendait pas  false
  fin à la fin                    false
  on continue                     2
*/

template <typename T>
int Field<T>::store(string contenuFichier,
		 size_t *pos1, size_t *pos2,
		 int flagSuperStatic){
  //######## col
  *pos2 = contenuFichier.find("|", *pos1);
  if (*pos2==contenuFichier.npos) return true;
  col = contenuFichier.substr(*pos1, (*pos2-*pos1));
  *pos1 = *pos2+1;

  return 2;
}

template <> inline
int Field<string>::reset() {
  col="#";
}

template <> inline
int Field<int>::reset() {
  col=0;
}

template <> inline
int Field<long>::reset() {
  col=0;
}

template <typename T>
int Field<T>::print() {
  saveHumain(&cout);
}

template <typename T>
int Field<T>::saveHumain(ostream * out) {
  *out << col   << "|";
}

template <typename T>
int Field<T>::saveShort(ostream * out) {
  *out << col   << "\t";
}

#endif
