#include "Vokabel.hpp"
#include "VokabelMenu.cpp"
#include "VokabelAIntegrerPlusTard.cpp"
#include "VokabelImportFichier.cpp"

//--------------------------------------------------------------------------------

int triTable::fautIlRedemander(int pos, int index) {
    if (levelR[index][pos] == false) return true;
  long deltaTemps = this->monTemps() - timeR[index][pos];
  return (deltaTemps/levelR[index][pos]) > 86400 ? true:false;
}

int triTable::reussite(int pos, int index) {
  timeR[index][pos] = this->monTemps();
  levelR[index][pos]++;
}
//
int triTable::echec(int pos, int index) {
    timeR[index][pos] = this->monTemps();
    if (levelR[index][pos]>0)
      levelR[index][pos]--;
}

//--------------------------------------------------------------------------------

void Vokabel::loadFile(string fileName) {
  cout << fileName << endl;
  maTriTable.stringR.loadFichierEntete(fileName);

  //ajouter autant d'enregistrement dans levelR et dans timeR qu'il y en a
  // dans maTriTable.stringR
  for (int i=maTriTable.levelR.size(); i<maTriTable.stringR.size(); i++) {
    maTriTable.levelR.add(0);
    maTriTable.timeR.add(this->monTemps());
  }
    
//  maTriTable.stringR.importTable(fileName);
//  maTriTable.levelR.set(0);
//  maTriTable.timeR.set(this->monTemps());
//  //ajouter autant d'enregistrement dans levelR et dans timeR qu'il y en a
//  // dans maTriTable.stringR
//  for (int i=maTriTable.levelR.size(); i<maTriTable.stringR.size(); i++) {
//    maTriTable.levelR.addVoid();
//    maTriTable.timeR.addVoid();
//  }
}

int Vokabel::invite(){
//  static struct termios oldt, newt;
//  int c;
  cout << endl << "?> ";
//
//  if (maTriTable.stringR.flagShot) {
//    tcgetattr( STDIN_FILENO, &oldt);
//    newt=oldt;
//    newt.c_lflag &= ~(ICANON);
//    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//
//    c=getc(stdin);
//
//    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
//    reponse=c;
//    if (c=='q') maTriTable.stringR.flagShot=false;
//  } else if (flagBlitz) {
//    tcgetattr( STDIN_FILENO, &oldt);
//    newt=oldt;
//    newt.c_lflag &= ~(ICANON);
//    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//
//    c=getc(stdin);
//
//    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
//    reponse=c;
//    if (c=='q') maTriTable.stringR.flagShot=false;
//  } else {
    cin.clear();
    getline(cin, reponse);
//  }
}

int Vokabel::interrogation(){
  cout << "interrogation ================================================" << endl;
  debug ("Vokabel", "interrogation", "size(): " + to_string(maTriTable.stringR.size()));
  for (;;) if(questionnaire()==false) exit(false);
}

int Vokabel::Echec(string maReponse) {
  string TempRecord;
  
//  Erreur.setNbColonnes(maTriTable.stringR.head::nbColonnes);
//  
//  for (int i=0; i<maTriTable.stringR.head::nbColonnes; i++) {
//    Erreur.stringR[0][i]= maTriTable.stringR[myRandom][i];
//    Erreur.levelR[0][i] = 0;
//    Erreur.timeR[0][i]  = this->monTemps();
//  }

  maTriTableNonSu.stringR.push_back(Erreur.stringR[0]);
  maTriTableNonSu.levelR.push_back(Erreur.levelR[0]);
  maTriTableNonSu.timeR.push_back(Erreur.timeR[0]);
  
  kurz("Mais non! c'était " + maReponse + "\n\n");

  //  MonField.echec(KEYINDEX, 0); //KEYINDEX??
//  if (maTriTable.stringR.flagMemo) kurz("indice: " + MonField.stringR[0][MEMOINDEX] + "\n");
//  if (maTriTable.stringR.flagShot) kurz("shot: "   + MonField.stringR[0][SHOTINDEX] + "\n");
  kurz ("\n");
}
int Vokabel::CBien(){
  kurz("C'est bien!\n");
  MonField.reussite(KEYINDEX, 0);
  saveFile();
}
////////////////////////////////////////

//int Vokabel::ShotMode() {
//  result = MonField.stringR[0][SHOTINDEX].compare(reponse);
//  if (result==0) {
//    CBien();
//    if (isFullySetVector()) return false;
//  } else 
//    Echec(MonField.stringR[0][SHOTINDEX]);
//}
//
//int Vokabel::BlitzMode() {
//  while (reponse.compare("?")==false) {
//    kurz ("Au cas où: " + MonField.stringR[0][STRINGINDEX] + "\n\n");
//    invite();
//  }
//  
//  if (reponse.compare("o")==false) {
//    kurz ("Pour vérif: " + MonField.stringR[0][STRINGINDEX] + "\n\n");
//    CBien();
//    if (isFullySetVector()) return false;
//
//  } else if (reponse.compare("f")==false) 
//    Echec(MonField.stringR[0][STRINGINDEX]);
//}
//
//int Vokabel::HasardMode() {
//  result = MonField.stringR[0][STRINGINDEX].compare(reponse);
//  if (result==0) {
//    CBien();
//
//    kurz (MonField.stringR[0][STRINGINDEX] + "\t");
//    for (int i=0; i < maTriTable.stringR.questionIndex.size(); i++)
//      kurz (maTriTable.stringR[myRandom][maTriTable.stringR.questionIndex[i]] + "\t");
//    kurz ("\n");
//      
//    if (isFullySetVector()){
//      if (flagApprentissageMode) {
//	maTriTable.stringR.size()+=5;
//	if (maTriTable.stringR.size()>maTriTable.stringR.size()) return false;
//      } else return false;
//    }
//  } else {
//    Echec(MonField.stringR[0][STRINGINDEX]);
//
//    kurz( MonField.stringR[0][STRINGINDEX] + "\t");
//    for (int i=0; i < maTriTable.stringR.questionIndex.size(); i++)
//      kurz (maTriTable.stringR[myRandom][maTriTable.stringR.questionIndex[i]] + "\t");
//    kurz ("\n");
//  }
//}

int Vokabel::NormalMode() {
  kurz("normal mode\n");
  result = MonField.stringR[0][STRINGINDEX].compare(reponse);
  if (result==0) {
    CBien();
//    
//    if (isFullySetVector()){
//      if (flagApprentissageMode) {
//	while (isFullySetVector()) maTriTable.stringR.size()+=5;
//	    
//	if (maTriTable.stringR.size()>maTriTable.stringR.size()) return false;
//      } else return false;
//    }
  } else 
    Echec(MonField.stringR[0][STRINGINDEX]);
}

////////////////////////////////////////////////////

int Vokabel::questionnaire () {
  myRandom=rand() % maTriTable.stringR.size();
//
//  if (flagHasard==true) {
//    int hasardQuestionIndex=rand() % maTriTable.stringR.questionIndex.size();
//    MonField.stringR[0][KEYINDEX] = maTriTable.stringR[myRandom][maTriTable.stringR.questionIndex[hasardQuestionIndex]];
//  } else{
//    
  MonField.stringR[0][KEYINDEX] = maTriTable.stringR[myRandom][maTriTable.stringR.questionIndex.back()];
//  };
//  
  MonField.stringR[0][STRINGINDEX] = maTriTable.stringR[myRandom][maTriTable.stringR.reponseIndex.back()];
//  if (maTriTable.stringR.flagMemo) MonField.stringR[0][MEMOINDEX] = maTriTable.stringR[myRandom][maTriTable.stringR.memoIndex.back()];
//  if (maTriTable.stringR.flagShot) MonField.stringR[0][SHOTINDEX] = maTriTable.stringR[myRandom][maTriTable.stringR.shotIndex.back()];
//  //############################################################
//  if (maTriTable.fautIlRedemander (0, maTriTable.stringR.questionIndex.back())!=false) {
    kurz("------------------------------------------------\n");
    kurz(MonField.stringR[0][KEYINDEX]+"\n");
//    
//    if ((flagMemoHide==false) && (maTriTable.stringR.flagMemo)) {
//      kurz("\t\tindice: " + MonField.stringR[0][MEMOINDEX] +"\n");
//      if (maTriTable.stringR.flagShot) kurz( "shot: " +  MonField.stringR[0][SHOTINDEX] +"\n\n");
//    }
//
    do {
      invite();
    } while(menu());
//
    alteReponseIndex=myRandom;

    //vérification proprement dite de la réponse
//    if (maTriTable.stringR.flagShot)              ShotMode();
//    else if (flagBlitz==true)  BlitzMode();
//    else if (flagHasard==true) HasardMode();
//    else
      NormalMode();

    alteReponseSens=sensQuestionnaire;
//}
  return true;
}

int Vokabel::isFullySetVector() {
//  if (maTriTable.stringR.flagShot==false) {
//    for (int i=0; i<maTriTable.stringR.size();i++)
//      if ( maTriTable.fautIlRedemander (i, maTriTable.stringR.questionIndex.back() ))
//	return false;
//  } else {
//    for (int i=0; i<maTriTable.stringR.size(); i++)
//      if ( maTriTable.fautIlRedemander (i, maTriTable.stringR.shotIndex.back() ))
	return false;
//  }      
//  return true;
}

Vokabel::Vokabel(int argc, char *argv[]){
  //  Erreur.setNbColonnes(maTriTable.stringR.head::nbColonnes);
  //  for (int i=0; i<4; i++) monField.add("");
}
  
Vokabel::~Vokabel(){}


int Vokabel::saveFile(){
//  string maReponse;
//  string extension=".save", fullFileName;
//  string extensionOrigine= maTriTable.stringR.fileName.substr(maTriTable.stringR.fileName.size()-5, 5);
//  //PROBLEME ce system fait que l'on ne peut avoir de nom de fichier de moins de cinq caractères.
//  if (extensionOrigine.compare(extension)!=0) 
//    fullFileName = maTriTable.stringR.fileName + extension;
//  else 
//    fullFileName = maTriTable.stringR.fileName;
//
//  ofstream out(fullFileName);
//  
//  debug ("Vokabel", "saveFile", "Sauvegarde du fichier======");
//  maTriTable.stringR.saveEntete(&out);
//  for (int i=0; i<maTriTable.stringR.size(); i++) 
//    maTriTable.stringR[i].saveHumain(&out);
//  debug ("Vokabel", "saveFile", "Sauvegarde effectué!=======");
//  return true;
}
