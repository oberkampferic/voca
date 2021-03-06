#include "Vokabel.hpp"

int Vokabel::swap(int index1, int index2) {
  string TempRecord;
  for (int i=0; i<20; i++) {
    TempRecord = recordSet[index1].vectorField[i].col;
    recordSet[index1].vectorField[i].col = recordSet[index2].vectorField[i].col;
    recordSet[index2].vectorField[i].col = TempRecord;
  }
}

int Vokabel::sort(int critere) {
  int k=0;
  for (int i=k++; i < recordSet.size(); i++){
    for (int j=i+1; j < recordSet.size(); j++) {
      if (recordSet[i].vectorField[critere].col.compare (recordSet[j].vectorField[critere].col) > 0)
	swap(i,j);
    }
  }
}

//== RECHERCHE =======================================================================================

int Vokabel::searchGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
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

int Vokabel::search(int critere, int critere2, string motif) {
  searchGen(recordSet, critere, critere2, motif);
}

int Vokabel::searchHauftig(int critere, int critere2, string motif) {
  searchGen(recordSetHauftig, critere, critere2, motif);
}

int Vokabel::searchDico(int critere, int critere2, string motif) {
  searchGen(recordSetDico, critere, critere2, motif);
}

//----------------------------------------------------------------------------------------------------
int Vokabel::searchInvGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
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

int Vokabel::searchInv(int critere, int critere2, string motif) {
  searchInvGen(recordSet, critere, critere2, motif);
}

int Vokabel::searchInvHauftig(int critere, int critere2, string motif) {
  searchInvGen(recordSetHauftig, critere, critere2, motif);
}

int Vokabel::searchInvDico(int critere, int critere2, string motif) {
  searchInvGen(recordSetDico, critere, critere2, motif);
}

//----------------------------------------------------------------------------------------------------

int Vokabel::searchInGen(vector<Record> & monRecordSet, int critere, int critere2, string motif) {
  cout << endl;
  for (int i=0; i< monRecordSet.size(); i++)
    if (monRecordSet[i].vectorField[critere].col.find (motif)!=string::npos) {
      cout << i << " : " << monRecordSet[i].vectorField[critere].col;
      if (critere2!=-1)
	cout << "\t\t" << monRecordSet[i].vectorField[critere2].col;
      cout << endl;
    }
}

int Vokabel::searchIn(int critere, int critere2, string motif) {
  searchInGen(recordSet, critere, critere2, motif);
}

int Vokabel::searchInHauftig(int critere, int critere2, string motif) {
  searchInGen(recordSetHauftig, critere, -1, motif);
}

int Vokabel::searchInDico(int critere, int critere2, string motif) {
  searchInGen(recordSetDico, critere, -1, motif);
}

//====================================================================================================

int Vokabel::aideMenu() {
  cout << "APPRENTISSAGE        passe en mode apprentissage           " << endl;
  cout << "BLITZ                permet d'éviter de saisir les réponses" << endl;
  cout << "COR1<PARAM>          correction colonne 1                  " << endl;
  cout << "COR2<PARAM>          correction colonne 2                  " << endl;
  cout << "DI                   nombres de questions à partir de 0    " << endl;
  cout << "EXIT                 sortie programme                      " << endl;
  cout << "HASARD               questions multiples                   " << endl;
  cout << "HELP                 this help                             " << endl;
  cout << "MEMO                 correction mémo                       " << endl;
  cout << "RESET                réinitialiser les scores              " << endl;
  cout << "PRINTALLSHORT        listing court de l'ensemble du fichier" << endl;
  cout << "PRINTALL             listing complet de tous le fichier    " << endl;
  cout << "PRINTSHORT           listing court de la sélection         " << endl;
  cout << "PRINT                listing complet                       " << endl;
  cout << "PRINTINDEX           listing des indexs                    " << endl;
  cout << "ILRESTE              listing de ce qui reste à apprendre   " << endl;
  cout << "SAVE                 sauvegarde de l'état du fichier       " << endl;
  cout << "S1                   chercher dans les réponses un motif   " << endl;
  cout << "S2                   chercher dans les questions un motif  " << endl;
  cout << "SHOT                 questionnaire sur une touche          " << endl;
  cout << "VERBOSE              bascule l'affichage des infos de debug" << endl;
}

//return true si interception d'un ordre
//return false si vraie réponse
int Vokabel::menu() {
    if(reponse.substr(0,13).compare("APPRENTISSAGE")==false){
      bascule(&flagApprentissageMode);
      flagCount=10;
      return true;
    }
    if (reponse.substr(0,5).compare("BLITZ")==false) {
      bascule (&flagBlitz);
      return true;
    }
    if (reponse.substr(0,4).compare("COR1")==false){
      recordSet[alteReponseIndex].vectorField[0].col=reponse.substr(5,reponse.size()-6);
      saveFile();
      return true;
    }
    if(reponse.substr(0,4).compare("COR2")==false){
      recordSet[alteReponseIndex].vectorField[1].col=reponse.substr(5,reponse.size()-6);
      saveFile();
      return true;
    }
    if (reponse.substr(0,2).compare("DI")==false) {
      cin >> flagCount;
      return true;
    }
    if (reponse.substr(0,4).compare("EXIT")==false) {
   for (int i=0; i<NBFENSTER; i++) delwin(myWindows[i]);
   endwin();
   cout << "Done.)" << endl;
      exit(false);
    }
    if (reponse.substr(0,6).compare("HASARD")==false) {
      bascule (&flagHasard);
      return true;
    }
    if(reponse.substr(0,4).compare("HELP")==false){
      aideMenu();
      return true;
    }
    if(reponse.substr(0,4).compare("MEMO")==false){
      recordSet[alteReponseIndex].vectorField[2].col=reponse.substr(5,reponse.size()-6);
      saveFile();
      return true;
    }
    if(reponse.substr(0,5).compare("RESET")==false){
      reset();
      return true;
    }
    if(reponse.substr(0,13).compare("PRINTALLSHORT")==false){
      printAllShort();
      return true;
    }
    if(reponse.substr(0,8).compare("PRINTALL")==false){
      printAll();
      return true;
    }
    if(reponse.substr(0,10).compare("PRINTINDEX")==false){
      printIndex();
      return true;
    }
    if(reponse.substr(0,10).compare("PRINTNONSU")==false){
      printErreur();
      return true;
    }
    if(reponse.substr(0,10).compare("PRINTSHORT")==false){
      printShort();
      return true;
    }
    if(reponse.substr(0,5).compare("PRINT")==false){
      print();
      return true;
    }
    if(reponse.substr(0,7).compare("ILRESTE")==false){
      reste();
      return true;
    }
    if (reponse.substr(0,4).compare("SAVE")==false) {
      saveFile();
      cout << "Sauvegarde terminé." << endl;
      return true;
    }
    if (reponse.substr(0,2).compare("S1")==false) {
      string motif;
      cin >> motif;
      searchIn(0,1, motif);
      cout << "Hauftig:----" << endl;
      searchInHauftig(1,0, motif);
      cout << "Dico:-------" << endl;
      searchInDico(1,0, motif);
      return true;
    }
    if (reponse.substr(0,2).compare("S2")==false) {
      string motif;
      cin >> motif;
      searchIn(1,0, motif);
      return true;
    }
    if (reponse.substr(0,3).compare("Sd1")==false) {
      string motif;
      cin >> motif;
      search(0,1, motif);
      cout << "Hauftig:----" << endl;
      searchHauftig(1, -1, motif);
      cout << "Dico:-------" << endl;
      searchDico(1, -1, motif);
      return true;
    }
    if (reponse.substr(0,3).compare("Sd2")==false) {
      string motif;
      cin >> motif;
      search(1, 0, motif);
      return true;
    }
    if (reponse.substr(0,3).compare("Se1")==false) {
      string motif;
      cin >> motif;
      searchInv(0,1, motif);
      cout << "Hauftig:----" << endl;
      searchInvHauftig(1, -1, motif);
      cout << "Dico:-------" << endl;
      searchInvDico(1, -1, motif);
      return true;
    }
    if (reponse.substr(0,3).compare("Se2")==false) {
      string motif;
      cin >> motif;
      searchInv(1, 0, motif);
      return true;
    }
    if (reponse.substr(0,4).compare("SHOT")==false) {
      if (shotIndex.size()>0) bascule (&flagShot);
      return true;
    }
    if (reponse.substr(0,7).compare("VERBOSE")==false) {
      bascule (&flagVerbose);
      return true;
    }
    
    if (reponse.substr(0,10).compare("VERIFINDEX")==false) {
      cout << "questionIndex.back():" << questionIndex.back() << endl;
      cout << "reponseIndex.back():" << reponseIndex.back() << endl;
      cout << "memoIndex.back():" << memoIndex.back() << endl;
      cout << "shotIndex.back():" << shotIndex.back() << endl;
      return true;
    }
  return false;
}

int Vokabel::print() {
  cout << "### CONTROLE DU VECTEUR ########################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].print();
}

int Vokabel::printErreur() {
  cout << "### CONTROLE DU VECTEUR ########################" << endl;
  for (int i=0; i<recordSetNonSu.size(); i++) recordSetNonSu[i].printShort();
}

int Vokabel::printShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].printShort();
}

int Vokabel::printAllShort() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].printShort();
}

int Vokabel::printAll() {
  cout << "### CONTROLE DU VECTEUR ENTIER #################" << endl;
  for (int i=0; i<recordSet.size(); i++) recordSet[i].print();
}

int Vokabel::reste() {
  cout << "### CONTROLE DE CE QUI RESTE A APPRENDRE #######" << endl;
  for (int i=0; i<flagCount; i++) recordSet[i].reste();
}

int Vokabel::loadFile(string fileName){
  kurz("Lecture du fichier=============================================\n");
  
  ifstream in(fileName);
  stringstream buffer;
  buffer << in.rdbuf();
  contenuFichier = buffer.str();
}
//true pas de problème
//false problème

int Vokabel::saveFile(){
  string maReponse;
  string extension=".save", fullFileName;
  string extensionOrigine= fileName.substr(fileName.size()-5, 5);
  //PROBLEME ce system fait que l'on ne peut avoir de nom de fichier de moins de cinq caractères.
  if (extensionOrigine.compare(extension)!=0) 
    fullFileName = fileName + extension;
  else 
    fullFileName = fileName;

  ofstream out(fullFileName);
  
  debug ("Vokabel", "saveFile", "Sauvegarde du fichier======");
  saveEntete(&out);
  for (int i=0; i<recordSet.size(); i++) 
    recordSet[i].saveHumain(&out);
  debug ("Vokabel", "saveFile", "Sauvegarde effectué!=======");
  return true;
}

int Vokabel::parsing(){
  unsigned int monNbColonnes;
  cout << "preparsing" << endl;
  preParsing(&contenuFichier);

  monNbColonnes = detectNbColonneInit(&contenuFichier);
  if (controleCoherenceFichier(&contenuFichier, monNbColonnes)==false) 
    erreur ("Vokabel", "parsing", "problème de cohérence, nombre de colonnes." + to_string(monNbColonnes));
  cout << "analyseEntete" << endl;
  size_t pos=analyseEntete(&contenuFichier);

  if (memoIndex.size()==0) flagMemo=false; else flagMemo=true;
  flagShot=false;

  contenuFichier=contenuFichier.substr(pos, contenuFichier.npos -pos);
    cout << "postparsing" << endl;
  postParsing(&contenuFichier);
  debug ("Vokabel", "parsing",  "contenuFichier:" + contenuFichier);
}

int Vokabel::storage(){ // return true si tt ok, false si pb
  kurz("Storage========================================================\n");

  size_t pos1=0, pos2;
  record monRecord; monRecord.setNbColonnes(nbColonnes);
  string str;
  int x=0; 

  for(;;) {
    flagCount++;
    cout << flagCount << "-";
    switch (monRecord.store(contenuFichier, &pos1, &pos2, flagSuperStatic)) {
    case true:  debug ("Vokabel", "storage", "Fin de boucle.");
      if (flagCount==-1) flagCount = x;                                        return true;
    case false: debug ("Vokabel", "storage", "Erreur innatendue.");            return false;
    case 2:     debug ("Vokabel", "storage", "Pas de problème, on continue."); break;
    }
    recordSet.push_back(monRecord);
    x++; 
  }
  cout << endl;
  erreur ("Vokabel", "storage", "Erreur fin de boucle.");

}
  
int Vokabel::storageHauftigste(){ // return true si tt ok, false si pb
  kurz("Storagehauftigste==================================================\n");

  size_t pos1=0, pos2;
  record monRecord; monRecord.setNbColonnes(nbColonnes);
  string str;
  int x=0; 

  for(;;) {
    flagCountHauftig++;
    //    cout << flagCountHauftig << "-";
    switch (monRecord.store(contenuFichier, &pos1, &pos2, flagSuperStatic)) {
    case true:  debug ("Vokabel", "storage", "Fin de boucle.");
      if (flagCountHauftig==-1) flagCountHauftig = x;                          return true;
    case false: debug ("Vokabel", "storage", "Erreur innatendue.");            return false;
    case 2:     debug ("Vokabel", "storage", "Pas de problème, on continue."); break;
    }
    recordSetHauftig.push_back(monRecord);
    x++; 
  }
  cout << endl;
  erreur ("Vokabel", "storage", "Erreur fin de boucle.");
}

int Vokabel::storageDico(){ // return true si tt ok, false si pb
  kurz("StorageDico==================================================\n");

  size_t pos1=0, pos2;
  record monRecord; monRecord.setNbColonnes(nbColonnes);
  string str;
  int x=0; 

  for(;;) {
    flagCountDico++;
    //    cout << flagCountDico << "-";
    switch (monRecord.store(contenuFichier, &pos1, &pos2, flagSuperStatic)) {
    case true:  debug ("Vokabel", "storage", "Fin de boucle.");
      if (flagCountDico==-1) flagCountDico = x;                                return true;
    case false: debug ("Vokabel", "storage", "Erreur innatendue.");            return false;
    case 2:     debug ("Vokabel", "storage", "Pas de problème, on continue."); break;
    }
    recordSetDico.push_back(monRecord);
    x++; 
  }
  cout << endl;
  erreur ("Vokabel", "storage", "Erreur fin de boucle.");
}


int Vokabel::reset() {
  kurz("### RÉINITIALISATION DU  VECTEUR ###############\n");
  for (int i=0; i<flagCount; i++)
    for (int j=0; j<4; j++) 
      recordSet[i].vectorField[j].reset();
}

Vokabel::Vokabel(int argc, char *argv[]){
  Erreur.setNbColonnes(nbColonnes);
}
  
Vokabel::~Vokabel(){}

int Vokabel::isFullySetVector() {
  if (flagShot==false) {
    for (int i=0; i<flagCount;i++)
      if ( recordSet[i].vectorField[questionIndex.back()].fautIlRedemander() )
	return false;
  } else {
    for (int i=0; i<flagCount;i++)
      if ( recordSet[i].vectorField[shotIndex.back()].fautIlRedemander() )
	return false;
  }      
	
  return true;
}

int Vokabel::invite(){
  static struct termios oldt, newt;
  int c;
  mvwgetstr(myWindows[0], 4, 9, str);  
  reponse.assign(str);
}

int Vokabel::interrogation(){
  cout << "interrogation ================================================" << endl;
  debug ("Vokabel", "interrogation", "flagCount: " + to_string(flagCount));
  for (;;) if(questionnaire()==false) exit(false);
}

int Vokabel::Echec(string maReponse) {
  string TempRecord;
  
  Erreur.setNbColonnes(nbColonnes);
  
  for (int i=0; i<nbColonnes; i++) {
    Erreur.vectorField[i].col=recordSet[myRandom].vectorField[i].col;
    Erreur.vectorField[i].level=0;
    Erreur.vectorField[i].time=monTemps();
  }

  cout << "là ca va" << endl;
  recordSetNonSu.push_back(Erreur);
  cout << "c bon!" << endl;
  
  kurz("Mais non! c'était " + maReponse + "\n\n");
  
  monField[0]->echec();
  if (flagMemo) kurz("indice: " + monField[MEMOINDEX]->col + "\n");
  if (flagShot) kurz("shot: "   + monField[SHOTINDEX]->col + "\n");
  kurz ("\n");
}

int Vokabel::CBien(){
  kurz("C'est bien!\n");
  monField[KEYINDEX]->reussite();
  saveFile();
}
////////////////////////////////////////

int Vokabel::ShotMode() {
  result = monField[SHOTINDEX]->col.compare(reponse);
  if (result==0) {
    CBien();
    if (isFullySetVector()) return false;
  } else 
    Echec(monField[SHOTINDEX]->col);
}

int Vokabel::BlitzMode() {
  while (reponse.compare("?")==false) {
    kurz ("Au cas où: " + monField[STRINGINDEX]->col + "\n\n");
    invite();
  }
  
  if (reponse.compare("o")==false) {
    kurz ("Pour vérif: " + monField[STRINGINDEX]->col + "\n\n");
    CBien();
    if (isFullySetVector()) return false;

  } else if (reponse.compare("f")==false) 
    Echec(monField[STRINGINDEX]->col);
}

int Vokabel::HasardMode() {
  result = monField[STRINGINDEX]->col.compare(reponse);
  if (result==0) {
    CBien();

    kurz (monField[STRINGINDEX]->col + "\t");
    for (int i=0; i < questionIndex.size(); i++)
      kurz (recordSet[myRandom].vectorField[questionIndex[i]].col + "\t");
    kurz ("\n");
      
    if (isFullySetVector()){
      if (flagApprentissageMode) {
	flagCount+=5;
	if (flagCount>recordSet.size()) return false;
      } else return false;
    }
  } else {
    Echec(monField[STRINGINDEX]->col);

    kurz( monField[STRINGINDEX]->col + "\t");
    for (int i=0; i < questionIndex.size(); i++)
      kurz (recordSet[myRandom].vectorField[questionIndex[i]].col + "\t");
    kurz ("\n");
  }
}

int Vokabel::NormalMode() {
  kurz("normal mode\n");
  result = monField[STRINGINDEX]->col.compare(reponse);
  if (result==0) {
    CBien();
    
    if (isFullySetVector()){
      if (flagApprentissageMode) {
	while (isFullySetVector()) flagCount+=5;
	    
	if (flagCount>recordSet.size()) return false;
      } else return false;
    }
  } else 
    Echec(monField[STRINGINDEX]->col);
}

////////////////////////////////////////////////////

int Vokabel::questionnaire () {
  //########################################
  myRandom=rand() % flagCount;
  if (flagHasard==true) {
    int hasardQuestionIndex=rand() % questionIndex.size();
    monField[KEYINDEX]= &recordSet[myRandom].vectorField[questionIndex[hasardQuestionIndex]];
  } else
    monField[KEYINDEX]= &recordSet[myRandom].vectorField[questionIndex.back()];
  
  monField[STRINGINDEX]= &recordSet[myRandom].vectorField[reponseIndex.back()];

  if (flagMemo) monField[MEMOINDEX] = &recordSet[myRandom].vectorField[memoIndex.back()];
  if (flagShot) monField[SHOTINDEX] = &recordSet[myRandom].vectorField[shotIndex.back()];

  //############################################################
  if (monField[KEYINDEX]->fautIlRedemander()!=false) {
    //    kurz("------------------------------------------------\n");
    //    kurz(monField[KEYINDEX]->col+"\n");
    
    if ((flagMemoHide==false) && (flagMemo)) {
      kurz("\t\tindice: " + monField[MEMOINDEX]->col +"\n");
      if (flagShot) kurz( "shot: " +  monField[SHOTINDEX]->col +"\n\n");
    }

    do {
      //Fenêtrage ########################################
      clear();
      //-- création de la fenêtre ----------------------------------------------------
      myWindows[0] = subwin(stdscr, 10, 79, 5, 0);
      myWindows[1] = subwin(stdscr, 10, 79, 17, 0);
      myWindows[2] = subwin(stdscr, 3, 79, 0,0);
      myWindows[3] = NULL;

      mesCouleursWindows();

      mvwprintw(myWindows[0], 1, 2, "GEGENWART ");    mvwprintw(myWindows[1], 1, 2, "LETZTE FRAGE:");
      mvwprintw(myWindows[0], 2, 2, "Frage:    ");    mvwprintw(myWindows[1], 2, 2, "Frage: ");
      mvwprintw(myWindows[0], 3, 2, "Indiz:    ");    mvwprintw(myWindows[1], 3, 2, "Indiz: ");
      mvwprintw(myWindows[0], 4, 2, "Losung:   ");    mvwprintw(myWindows[1], 4, 2, "Losung:");
      mvwprintw(myWindows[1], 5, 2, "Deine: ");

      mvwprintw(myWindows[0], 2, 9, monField[KEYINDEX]->col.c_str());
      mvwprintw(myWindows[0], 3, 9, monField[MEMOINDEX]->col.c_str());

      mvwprintw(myWindows[1], 2, 9, recordSet[alteReponseIndex].vectorField[STRINGINDEX].col.c_str());
      mvwprintw(myWindows[1], 3, 9, recordSet[alteReponseIndex].vectorField[MEMOINDEX].col.c_str());
      mvwprintw(myWindows[1], 4, 9, recordSet[alteReponseIndex].vectorField[KEYINDEX].col.c_str());

      mvwprintw(myWindows[1], 5, 9, str);

      //-- création de la fenêtre ----------------------------------------------------
      mesCouleursWindows2();
      
      invite();

      flash(); beep();
      //~Fenêtrage ########################################

    } while(menu());

    alteReponseIndex=myRandom;
    //vérification proprement dite de la réponse

    if (flagShot)              ShotMode();
    else if (flagBlitz==true)  BlitzMode();
    else if (flagHasard==true) HasardMode();
    else                       NormalMode();

    alteReponseSens=sensQuestionnaire;
  }

  return true;
}
