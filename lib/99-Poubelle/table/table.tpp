template<typename T>
void table<T>::importTable(string filename) {
  loadFile(filename);
  parsing();
  if (!this->storage(contenuFichier))
    erreur("pedagogie","pedagogieLoadFile", filename + "Problème1.");
}

template<typename T>
int table<T>::loadFile(string fileName){
  kurz("Lecture du fichier=============================================\n");
  ifstream in(fileName);
  stringstream buffer;
  buffer << in.rdbuf();
  contenuFichier = buffer.str();
}

template<typename T>
int table<T>::parsing(){
  unsigned int monNbColonnes;
  cout << "preparsing" << endl;
  preParsing(&contenuFichier);

  monNbColonnes = detectNbColonneInit(&contenuFichier);
  if (controleCoherenceFichier(&contenuFichier, monNbColonnes)==false) 
    erreur ("table", "parsing", "problème de cohérence, nombre de colonnes." + to_string(monNbColonnes));
  cout << "analyseEntete" << endl;
  size_t pos=analyseEntete(&contenuFichier);
  
  if (memoIndex.size()==0) flagMemo=false; else flagMemo=true;
  flagShot=false;

  contenuFichier=contenuFichier.substr(pos, contenuFichier.npos -pos);
  cout << "postparsing" << endl;
  postParsing(&contenuFichier);
  debug ("table", "parsing",  "contenuFichier:" + contenuFichier);

  recordSet<T>::nbColonnes=monNbColonnes;
  cout << "recordSet::nbColonnes:" << nbColonnes << endl;
  cout << "fin" << endl;
}
