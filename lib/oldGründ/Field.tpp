#ifndef FIELDTPP
#define FIELDTPP

//template <typename T>
//void Field<T>::Field(){
//
//}

template <typename T>
void Field<T>::init(T valeur){
  col=valeur;  
}

template <> inline  Field<string>::Field(){  col= "#"; }
template <> inline  Field<int   >::Field(){  col= 0;   }
template <> inline  Field<long  >::Field(){  col= 0;   }

template <> inline Field<string>::Field(string valeur){  col= valeur;}
template <> inline Field<int   >::Field(int    valeur){  col= valeur;}
template <> inline Field<long  >::Field(long   valeur){  col= valeur;}

//--------------------------------------------------
template <> inline void Field<string>::init(){  col= "#"; }
template <> inline void Field<int   >::init(){  col= 0;   }
template <> inline void Field<long  >::init(){  col= 0;   }
//--------------------------------------------------

template <typename T>
void Field<T>::set(T valeur){ //Non testé
  col=valeur;
}

template <typename T>
T Field<T>::get(){ //Non testé
  return col;
}

template <typename T>
int Field<T>::isSet(T valeur){ //Non testé
  return (col==valeur) ? true:false;
}

template <> inline
int Field<string>::store(string contenuFichier,
		 size_t *pos1, size_t *pos2,
		 int flagSuperStatic){
  *pos2 = contenuFichier.find("|", *pos1);
  if (*pos2==contenuFichier.npos) return true;
  col = contenuFichier.substr(*pos1, (*pos2-*pos1));
  *pos1 = *pos2+1;

  return 2;
}

template <> inline int Field<string>::reset() {  col="#"; }
template <> inline int Field<   int>::reset() {  col=0  ; }
template <> inline int Field<  long>::reset() {  col=0  ; }

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
