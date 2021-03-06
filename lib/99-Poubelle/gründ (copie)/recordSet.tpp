template<typename T>
void recordSet<T>::init(T valeur) {
  for (int i=0; i < recordSet.size(); i++){
    recordSet[i].init(valeur);
  }
}

template<typename T>
int recordSet<T>::swap(int index1, int index2) {
  string TempRecord;
  for (int i=0; i<20; i++) {
    TempRecord = recordSet[index1].record[i].col;
    recordSet[index1].record[i].col = recordSet[index2].record[i].col;
    recordSet[index2].record[i].col = TempRecord;
  } }

template<typename T>
int recordSet<T>::sort(int critere) {
  int k=0;
  for (int i=k++; i < recordSet.size(); i++){
    for (int j=i+1; j < recordSet.size(); j++) {
      if (recordSet[i].record[critere].col.compare (recordSet[j].record[critere].col) > 0)
	swap(i,j);
    } } }

//== RECHERCHE =======================================================================================

template<typename T>
int recordSet<T>::search(int critere, int critere2, string motif) {
  cout << endl;
  
  for (int i=0; i< recordSet.size(); i++){
    //Mise en Majuscule à cause des substantifs Allemands.
    string montexte = recordSet[i].record[critere].col.substr(0,motif.size());
    boost::to_upper(montexte);
    string monMotif = motif;
    boost::to_upper(monMotif);
    
    if (montexte.compare(monMotif)==0) {
      cout << i << " : " << recordSet[i].record[critere].col;
      if (critere2!=-1)
	cout << "\t\t" << recordSet[i].record[critere2].col;
      cout << endl;
    } } }

//----------------------------------------------------------------------------------------------------
template<typename T>
int recordSet<T>::searchInv(int critere, int critere2, string motif) {
  cout << endl;
  int taille;
  
  for (int i=0; i< recordSet.size(); i++){
    
    taille=recordSet[i].record[critere].col.size();
    if(taille>=motif.size()) {
      if (recordSet[i].record[critere].col.substr(taille-motif.size(),taille).compare(motif)==0) {

	//########################################
	cout << i << " : " << recordSet[i].record[critere].col;
	if (critere2!=-1)
	  cout << "\t\t" << recordSet[i].record[critere2].col;
	cout << endl;
      } } } }

//----------------------------------------------------------------------------------------------------

template<typename T>
int recordSet<T>::searchIn(int critere, int critere2, string motif) {
  cout << endl;

  for (int i=0; i< recordSet.size(); i++)
    if (recordSet[i].record[critere].col.find (motif)!=string::npos) {
      cout << i << " : " << recordSet[i].record[critere].col;
      if (critere2!=-1)
	cout << "\t\t" << recordSet[i].record[critere2].col;
      cout << endl;
    } }

//######################################################################
template<typename T>
int recordSet<T>::print() {
  cout << "### CONTROLE DU VECTEUR ########################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].print();
}

template<typename T>
int recordSet<T>::printShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].printShort();
}

template<typename T>
int recordSet<T>::printAllShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].printShort();
}

template<typename T>
int recordSet<T>::printAll() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].print();
}

template<typename T>
int recordSet<T>::reste() {
  cout << "### CONTROLE DE CE QUI RESTE A APPRENDRE #######" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].reste();
}

//######################################################################

template<typename T>
int recordSet<T>::reset() {
  cout << "### RÉINITIALISATION DU  VECTEUR ###############\n" << endl;
  for (int i=0; i<flagCount; i++)
    for (int j=0; j<4; j++) 
      recordSet[i].record[j].reset();
}

template<typename T>
int recordSet<T>::import(ifstream &in) {
  
}

template<typename T>
int recordSet<T>::storage (string & contenuFichier) {
  kurz("Storage========================================================\n");

  size_t pos1=0, pos2;
  record<string> monRecord; monRecord.setNbColonnes(nbColonnes);
  string str;
  int x=0; 

  for(;;) {
    flagCount++;
    switch (monRecord.store(contenuFichier, &pos1, &pos2, flagSuperStatic)) {
    case true:  debug ("recordSet", "storage", "Fin de boucle.");
      if (flagCount==-1) flagCount = x;                                        return true;
    case false: debug ("recordSet", "storage", "Erreur innatendue.");            return false;
    case 2:     debug ("recordSet", "storage", "Pas de problème, on continue."); break;
    }
    recordSet.push_back(monRecord);
    x++; 
  }
  cout << endl;
  erreur ("recordSet", "storage", "Erreur fin de boucle.");
}

template<typename T>
void recordSet<T>::addVoid () {
  record<T> monRecord;
  monRecord.setNbColonnes(nbColonnes);
  monRecord.init();
  recordSet.push_back(monRecord);
}

template<typename T>
int recordSet<T>::saveHumain(ofstream &out) {
  //  string maReponse;
  //  string extension=".save", fullFileName;
  //  string extensionOrigine= fileName.substr(fileName.size()-5, 5);
  //  //PROBLEME ce system fait que l'on ne peut avoir de nom de fichier de moins de cinq caractères.
  //  if (extensionOrigine.compare(extension)!=0) 
  //    fullFileName = fileName + extension;
  //  else 
  //    fullFileName = fileName;
  //
  //  ofstream out(fullFileName);
  //  
  //  debug ("recordSet", "saveFile", "Sauvegarde du fichier======");
  //  saveEntete(&out);
  //  for (int i=0; i<recordSet.size(); i++) 
  //    recordSet[i].saveHumain(&out);
  //  debug ("recordSet", "saveFile", "Sauvegarde effectué!=======");
  //  return true;
}

//######################################################################
