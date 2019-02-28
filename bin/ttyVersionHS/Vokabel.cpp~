#include "Vokabel.hpp"
#include "VokabelMenu.cpp"
#include "VokabelAIntegrerPlusTard.cpp"
#include "VokabelImportFichier.cpp"

//--------------------------------------------------------------------------------

int triptysch::fautIlRedemander(int pos, int index) {
  //if (levelR(index,pos) == false) return true;
    if (levelR.monRecordSet[index][pos] == false) return true;
  long deltaTemps = this->monTemps() - timeR.monRecordSet[index][pos];
  return (deltaTemps/levelR.monRecordSet[index][pos]) > 86400 ? true:false;
}

int triptysch::reussite(int pos, int index) {
  timeR.monRecordSet[index][pos] = this->monTemps();
  levelR.monRecordSet[index][pos]++;
}

int triptysch::echec(int pos, int index) {
    timeR.monRecordSet[index][pos] = this->monTemps();
    if (levelR.monRecordSet[index][pos]>0)
      levelR.monRecordSet[index][pos]--;
}

//--------------------------------------------------------------------------------

void Vokabel::pedagogieLoadFile(string fileName, triptysch * myRecordSet) {
  cout << fileName << endl;
  
  monTriptyshRecordSet.stringR.importTable(fileName);
  monTriptyshRecordSet.levelR.set(0);
  monTriptyshRecordSet.timeR.set(this->monTemps());
  //ajouter autant d'enregistrement dans levelR et dans timeR qu'il y en a
  // dans monTriptyshRecordSet.stringR
  for (int i=monTriptyshRecordSet.levelR.flagCount; i<monTriptyshRecordSet.stringR.flagCount; i++) {
    monTriptyshRecordSet.levelR.addVoid();
    monTriptyshRecordSet.timeR.addVoid();
  }
}

int Vokabel::invite(){
  static struct termios oldt, newt;
  int c;
  cout << endl << "?> ";

  if (monTriptyshRecordSet.stringR.flagShot) {
    tcgetattr( STDIN_FILENO, &oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    c=getc(stdin);

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    reponse=c;
    if (c=='q') monTriptyshRecordSet.stringR.flagShot=false;
  } else if (flagBlitz) {
    tcgetattr( STDIN_FILENO, &oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    c=getc(stdin);

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    reponse=c;
    if (c=='q') monTriptyshRecordSet.stringR.flagShot=false;
  } else {
    cin.clear();
    getline(cin, reponse);
  }
}

int Vokabel::interrogation(){
  cout << "interrogation ================================================" << endl;
  debug ("Vokabel", "interrogation", "flagCount: " + to_string(monTriptyshRecordSet.stringR.flagCount));
  for (;;) if(questionnaire()==false) exit(false);
}

int Vokabel::Echec(string maReponse) {
  string TempRecord;
  
  Erreur.setNbColonnes(monTriptyshRecordSet.stringR.head::nbColonnes);
  
  for (int i=0; i<monTriptyshRecordSet.stringR.head::nbColonnes; i++) {
    Erreur.stringR.monRecordSet[0][i]= monTriptyshRecordSet.stringR.monRecordSet[myRandom][i];
    Erreur.levelR.monRecordSet[0][i] = 0;
    Erreur.timeR.monRecordSet[0][i]  = this->monTemps();
  }

  monTriptyshRecordSetNonSu.stringR.monRecordSet.push_back(Erreur.stringR.monRecordSet[0]);
  monTriptyshRecordSetNonSu.levelR.monRecordSet.push_back(Erreur.levelR.monRecordSet[0]);
   monTriptyshRecordSetNonSu.timeR.monRecordSet.push_back(Erreur.timeR.monRecordSet[0]);
  
  kurz("Mais non! c'était " + maReponse + "\n\n");

  MonField.echec(KEYINDEX, 0); //KEYINDEX??
  if (monTriptyshRecordSet.stringR.flagMemo) kurz("indice: " + MonField.stringR.monRecordSet[0][MEMOINDEX] + "\n");
  if (monTriptyshRecordSet.stringR.flagShot) kurz("shot: "   + MonField.stringR.monRecordSet[0][SHOTINDEX] + "\n");
  kurz ("\n");
}
int Vokabel::CBien(){
  kurz("C'est bien!\n");
  MonField.reussite(KEYINDEX, 0);
  saveFile();
}
////////////////////////////////////////

int Vokabel::ShotMode() {
  result = MonField.stringR.monRecordSet[0][SHOTINDEX].compare(reponse);
  if (result==0) {
    CBien();
    if (isFullySetVector()) return false;
  } else 
    Echec(MonField.stringR.monRecordSet[0][SHOTINDEX]);
}

int Vokabel::BlitzMode() {
  while (reponse.compare("?")==false) {
    kurz ("Au cas où: " + MonField.stringR.monRecordSet[0][STRINGINDEX] + "\n\n");
    invite();
  }
  
  if (reponse.compare("o")==false) {
    kurz ("Pour vérif: " + MonField.stringR.monRecordSet[0][STRINGINDEX] + "\n\n");
    CBien();
    if (isFullySetVector()) return false;

  } else if (reponse.compare("f")==false) 
    Echec(MonField.stringR.monRecordSet[0][STRINGINDEX]);
}

int Vokabel::HasardMode() {
  result = MonField.stringR.monRecordSet[0][STRINGINDEX].compare(reponse);
  if (result==0) {
    CBien();

    kurz (MonField.stringR.monRecordSet[0][STRINGINDEX] + "\t");
    for (int i=0; i < monTriptyshRecordSet.stringR.questionIndex.size(); i++)
      kurz (monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.questionIndex[i]] + "\t");
    kurz ("\n");
      
    if (isFullySetVector()){
      if (flagApprentissageMode) {
	monTriptyshRecordSet.stringR.flagCount+=5;
	if (monTriptyshRecordSet.stringR.flagCount>monTriptyshRecordSet.stringR.monRecordSet.size()) return false;
      } else return false;
    }
  } else {
    Echec(MonField.stringR.monRecordSet[0][STRINGINDEX]);

    kurz( MonField.stringR.monRecordSet[0][STRINGINDEX] + "\t");
    for (int i=0; i < monTriptyshRecordSet.stringR.questionIndex.size(); i++)
      kurz (monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.questionIndex[i]] + "\t");
    kurz ("\n");
  }
}

int Vokabel::NormalMode() {
  kurz("normal mode\n");
  result = MonField.stringR.monRecordSet[0][STRINGINDEX].compare(reponse);
  if (result==0) {
    CBien();
    
    if (isFullySetVector()){
      if (flagApprentissageMode) {
	while (isFullySetVector()) monTriptyshRecordSet.stringR.flagCount+=5;
	    
	if (monTriptyshRecordSet.stringR.flagCount>monTriptyshRecordSet.stringR.monRecordSet.size()) return false;
      } else return false;
    }
  } else 
    Echec(MonField.stringR.monRecordSet[0][STRINGINDEX]);
}

////////////////////////////////////////////////////

int Vokabel::questionnaire () {
  myRandom=rand() % monTriptyshRecordSet.stringR.flagCount;

  if (flagHasard==true) {
    int hasardQuestionIndex=rand() % monTriptyshRecordSet.stringR.questionIndex.size();
    MonField.stringR.monRecordSet[0][KEYINDEX] = monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.questionIndex[hasardQuestionIndex]];
  } else{
    
    MonField.stringR.monRecordSet[0][KEYINDEX] = monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.questionIndex.back()];
  };
  
  MonField.stringR.monRecordSet[0][STRINGINDEX] = monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.reponseIndex.back()];
  if (monTriptyshRecordSet.stringR.flagMemo) MonField.stringR.monRecordSet[0][MEMOINDEX] = monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.memoIndex.back()];
  if (monTriptyshRecordSet.stringR.flagShot) MonField.stringR.monRecordSet[0][SHOTINDEX] = monTriptyshRecordSet.stringR.monRecordSet[myRandom][monTriptyshRecordSet.stringR.shotIndex.back()];
  //############################################################
  if (monTriptyshRecordSet.fautIlRedemander (0, monTriptyshRecordSet.stringR.questionIndex.back())!=false) {
    kurz("------------------------------------------------\n");
    kurz(MonField.stringR.monRecordSet[0][KEYINDEX]+"\n");
    
    if ((flagMemoHide==false) && (monTriptyshRecordSet.stringR.flagMemo)) {
      kurz("\t\tindice: " + MonField.stringR.monRecordSet[0][MEMOINDEX] +"\n");
      if (monTriptyshRecordSet.stringR.flagShot) kurz( "shot: " +  MonField.stringR.monRecordSet[0][SHOTINDEX] +"\n\n");
    }

    do {
      invite();
    } while(menu());

    alteReponseIndex=myRandom;

    //vérification proprement dite de la réponse
    if (monTriptyshRecordSet.stringR.flagShot)              ShotMode();
    else if (flagBlitz==true)  BlitzMode();
    else if (flagHasard==true) HasardMode();
    else                       NormalMode();

    alteReponseSens=sensQuestionnaire;
  }
  return true;
}

int Vokabel::isFullySetVector() {
  if (monTriptyshRecordSet.stringR.flagShot==false) {
    for (int i=0; i<monTriptyshRecordSet.stringR.flagCount;i++)
      if ( monTriptyshRecordSet.fautIlRedemander (i, monTriptyshRecordSet.stringR.questionIndex.back() ))
	return false;
  } else {
    for (int i=0; i<monTriptyshRecordSet.stringR.flagCount; i++)
      if ( monTriptyshRecordSet.fautIlRedemander (i, monTriptyshRecordSet.stringR.shotIndex.back() ))
	return false;
  }      
  return true;
}

Vokabel::Vokabel(int argc, char *argv[]){
  Erreur.setNbColonnes(monTriptyshRecordSet.stringR.head::nbColonnes);
}
  
Vokabel::~Vokabel(){}


int Vokabel::saveFile(){
  string maReponse;
  string extension=".save", fullFileName;
  string extensionOrigine= monTriptyshRecordSet.stringR.fileName.substr(monTriptyshRecordSet.stringR.fileName.size()-5, 5);
  //PROBLEME ce system fait que l'on ne peut avoir de nom de fichier de moins de cinq caractères.
  if (extensionOrigine.compare(extension)!=0) 
    fullFileName = monTriptyshRecordSet.stringR.fileName + extension;
  else 
    fullFileName = monTriptyshRecordSet.stringR.fileName;

  ofstream out(fullFileName);
  
  debug ("Vokabel", "saveFile", "Sauvegarde du fichier======");
  monTriptyshRecordSet.stringR.saveEntete(&out);
  for (int i=0; i<monTriptyshRecordSet.stringR.monRecordSet.size(); i++) 
    monTriptyshRecordSet.stringR.monRecordSet[i].saveHumain(&out);
  debug ("Vokabel", "saveFile", "Sauvegarde effectué!=======");
  return true;
}
