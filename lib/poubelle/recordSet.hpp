class recordSet: public commun {
  int flagCount=-1;
  
  vector<record> monRecordSet;
  int swap(int index1, int index2);
  int sort(int critere);
  //###########################################################
  int searchGen       (vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int search          (int critere, int critere2, string motif);
  int searchInvGen    (vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int searchInv       (int critere, int critere2, string motif);
  int searchInGen     (vector<Record> & monRecordSet, int critere, int critere2, string motif);
  int searchIn        (int critere, int critere2, string motif);
  //###########################################################
  int print();
  int printShort();
  int printAllShort();
  int printAll();
  int reste();
  //###########################################################
  int import(ifstream &in);                  //quel sens?
  int storage(string &contenuFichier);     //prends une chaine déjà formaté et l'ajoute
  int saveHumain(ofstream &out);
  
};
  

