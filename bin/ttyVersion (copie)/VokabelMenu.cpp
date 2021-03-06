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
//    if(reponse.substr(0,13).compare("APPRENTISSAGE")==false){
//      bascule(&flagApprentissageMode);
//      flagCount=10;
//      return true;
//    }
//    if (reponse.substr(0,5).compare("BLITZ")==false) {
//      bascule (&flagBlitz);
//      return true;
//    }
//    if (reponse.substr(0,4).compare("COR1")==false){
//      recordSet[alteReponseIndex].vectorField[0].col=reponse.substr(5,reponse.size()-6);
//      saveFile();
//      return true;
//    }
//    if(reponse.substr(0,4).compare("COR2")==false){
//      recordSet[alteReponseIndex].vectorField[1].col=reponse.substr(5,reponse.size()-6);
//      saveFile();
//      return true;
//    }
//    if (reponse.substr(0,2).compare("DI")==false) {
//      cin >> flagCount;
//      return true;
//    }
//    if (reponse.substr(0,4).compare("EXIT")==false) {
//      cout << "Done.)" << endl;
//      exit(false);
//    }
//    if (reponse.substr(0,6).compare("HASARD")==false) {
//      bascule (&flagHasard);
//      return true;
//    }
//    if(reponse.substr(0,4).compare("HELP")==false){
//      aideMenu();
//      return true;
//    }
//    if(reponse.substr(0,4).compare("MEMO")==false){
//      recordSet[alteReponseIndex].vectorField[2].col=reponse.substr(5,reponse.size()-6);
//      saveFile();
//      return true;
//    }
//    if(reponse.substr(0,5).compare("RESET")==false){
//      reset();
//      return true;
//    }
//    if(reponse.substr(0,13).compare("PRINTALLSHORT")==false){
//      printAllShort();
//      return true;
//    }
//    if(reponse.substr(0,8).compare("PRINTALL")==false){
//      printAll();
//      return true;
//    }
//    if(reponse.substr(0,10).compare("PRINTINDEX")==false){
//      printIndex();
//      return true;
//    }
//    if(reponse.substr(0,10).compare("PRINTNONSU")==false){
//      printErreur();
//      return true;
//    }
//    if(reponse.substr(0,10).compare("PRINTSHORT")==false){
//      printShort();
//      return true;
//    }
//    if(reponse.substr(0,5).compare("PRINT")==false){
//      print();
//      return true;
//    }
//    if(reponse.substr(0,7).compare("ILRESTE")==false){
//      reste();
//      return true;
//    }
//    if (reponse.substr(0,4).compare("SAVE")==false) {
//      saveFile();
//      cout << "Sauvegarde terminé." << endl;
//      return true;
//    }
//    if (reponse.substr(0,2).compare("S1")==false) {
//      string motif;
//      cin >> motif;
//      searchIn(0,1, motif);
//      cout << "Hauftig:----" << endl;
//      searchInHauftig(1,0, motif);
//      cout << "Dico:-------" << endl;
//      searchInDico(1,0, motif);
//      return true;
//    }
//    if (reponse.substr(0,2).compare("S2")==false) {
//      string motif;
//      cin >> motif;
//      searchIn(1,0, motif);
//      return true;
//    }
//    if (reponse.substr(0,3).compare("Sd1")==false) {
//      string motif;
//      cin >> motif;
//      search(0,1, motif);
//      cout << "Hauftig:----" << endl;
//      searchHauftig(1, -1, motif);
//      cout << "Dico:-------" << endl;
//      searchDico(1, -1, motif);
//      return true;
//    }
//    if (reponse.substr(0,3).compare("Sd2")==false) {
//      string motif;
//      cin >> motif;
//      search(1, 0, motif);
//      return true;
//    }
//    if (reponse.substr(0,3).compare("Se1")==false) {
//      string motif;
//      cin >> motif;
//      searchInv(0,1, motif);
//      cout << "Hauftig:----" << endl;
//      searchInvHauftig(1, -1, motif);
//      cout << "Dico:-------" << endl;
//      searchInvDico(1, -1, motif);
//      return true;
//    }
//    if (reponse.substr(0,3).compare("Se2")==false) {
//      string motif;
//      cin >> motif;
//      searchInv(1, 0, motif);
//      return true;
//    }
//    if (reponse.substr(0,4).compare("SHOT")==false) {
//      if (shotIndex.size()>0) bascule (&flagShot);
//      return true;
//    }
//    if (reponse.substr(0,7).compare("VERBOSE")==false) {
//      bascule (&flagVerbose);
//      return true;
//    }
//    
//    if (reponse.substr(0,10).compare("VERIFINDEX")==false) {
//      cout << "questionIndex.back():" << questionIndex.back() << endl;
//      cout << "reponseIndex.back():" << reponseIndex.back() << endl;
//      cout << "memoIndex.back():" << memoIndex.back() << endl;
//      cout << "shotIndex.back():" << shotIndex.back() << endl;
//      return true;
//    }
  return false;
}
