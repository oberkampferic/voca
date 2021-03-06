int recordSet::swap(int index1, int index2) {
  string TempRecord;
  for (int i=0; i<20; i++) {
    TempRecord = recordSet[index1].vectorField[i].col;
    recordSet[index1].vectorField[i].col = recordSet[index2].vectorField[i].col;
    recordSet[index2].vectorField[i].col = TempRecord;
  }
}

int recordSet::sort(int critere) {
  int k=0;
  for (int i=k++; i < recordSet.size(); i++){
    for (int j=i+1; j < recordSet.size(); j++) {
      if (recordSet[i].vectorField[critere].col.compare (recordSet[j].vectorField[critere].col) > 0)
	swap(i,j);
    }
  }
}

//== RECHERCHE =======================================================================================

int recordSet::searchGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
  cout << endl;
  for (int i=0; i< monRecordSet.size(); i++){
    string montexte = monRecordSet[i].vectorField[critere].col.substr(0,motif.size());
    boost::to_upper(montexte);
    string monMotif = motif;
    boost::to_upper(monMotif);
    if (montexte.compare(monMotif)==0) {
      //          if (monRecordSet[i].vectorField[critere].col.substr(0,motif.size()).compare(motif)==0) {
      cout << i << " : " << monRecordSet[i].vectorField[critere].col;
      if (critere2!=-1)
	cout << "\t\t" << monRecordSet[i].vectorField[critere2].col;
      cout << endl;
    }
  }
}

int recordSet::search(int critere, int critere2, string motif) {
  searchGen(recordSet, critere, critere2, motif);
}

//----------------------------------------------------------------------------------------------------
int recordSet::searchInvGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
  cout << endl;
  int taille;
  for (int i=0; i< monRecordSet.size(); i++){
    taille=monRecordSet[i].vectorField[critere].col.size();
    if(taille>=motif.size()) {
      if (monRecordSet[i].vectorField[critere].col.substr(taille-motif.size(),taille).compare(motif)==0) {
	cout << i << " : " << monRecordSet[i].vectorField[critere].col;
	if (critere2!=-1)
	  cout << "\t\t" << monRecordSet[i].vectorField[critere2].col;
	cout << endl;
      }
    }
  }
}

int recordSet::searchInv(int critere, int critere2, string motif) {
  searchInvGen(recordSet, critere, critere2, motif);
}

//----------------------------------------------------------------------------------------------------

int recordSet::searchInGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
  cout << endl;
  for (int i=0; i< monRecordSet.size(); i++)
    if (monRecordSet[i].vectorField[critere].col.find (motif)!=string::npos) {
      cout << i << " : " << monRecordSet[i].vectorField[critere].col;
      if (critere2!=-1)
	cout << "\t\t" << monRecordSet[i].vectorField[critere2].col;
      cout << endl;
    }
}

int recordSet::searchIn(int critere, int critere2, string motif) {
  searchInGen(recordSet, critere, critere2, motif);
}

//######################################################################

int recordSet::print() {
  cout << "### CONTROLE DU VECTEUR ########################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].print();
}

int recordSet::printShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].printShort();
}

int recordSet::printAllShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].printShort();
}

int recordSet::printAll() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].print();
}

int recordSet::reste() {
  cout << "### CONTROLE DE CE QUI RESTE A APPRENDRE #######" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].reste();
}

//######################################################################

int recordSet::import(&in) {
  
}

int recordSet::contenuFichier(&in) {
  
}

int recordSet::saveHumain(&out) {
  
}

//######################################################################
