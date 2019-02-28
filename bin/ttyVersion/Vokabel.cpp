 #include "Vokabel.hpp"

int triTable::fautIlRedemander(int pos, int index) {
    if (lvl_rcdSET[index][pos] == false) return true;
  long deltaTemps = this->monTemps() - tim_rcdSET[index][pos];
  return (deltaTemps/lvl_rcdSET[index][pos]) > 86400 ? true:false;
}

int triTable::reussite(int pos, int index) {
  tim_rcdSET[index][pos] = this->monTemps();
  lvl_rcdSET[index][pos]++;
}

int triTable::echec(int pos, int index) {
    tim_rcdSET[index][pos] = this->monTemps();
    if (lvl_rcdSET[index][pos]>0)
      lvl_rcdSET[index][pos]--;
}
//###########################################################

void Vokabel::loadFile(string fileName) {
  cout << fileName << endl;
  str_rcdSET.loadFichierEntete(fileName);
  cout << "storage ended\n";
  //ajouter autant d'enregistrement dans lvl_rcdSET et dans tim_rcdSET
  // qu'il y en a dans str_rcdSET
  //Initialisation des tables de temps et ne niveau du RecordSet
  for (int i=lvl_rcdSET.size(); i<str_rcdSET.size(); i++) {
    lvl_rcdSET.add();
    tim_rcdSET.add();
    for (int j=lvl_rcdSET[i].size(); j<str_rcdSET[i].size(); j++) {
      lvl_rcdSET[i].add(0);
      tim_rcdSET[i].add(this->monTemps());
    }
  }
  //Initialisation du champs Reponse
  for (int i=0; i< str_rcdSET[0].size(); i++)
    MonField.add("");

  cout << "init ended" << endl;
}

//-----------------------------------------------------------
int Vokabel::invite(){
  cout << endl << "?> ";
  cin.clear();
  getline(cin, reponse);
}

int Vokabel::interrogation(){
  cout << "interrogation =====================================" << endl;
  message ("Vokabel", "interrogation", "size(): " + to_string(str_rcdSET.size()));
  for (;;) if(questionnaire()==false) exit(false);
}

int Vokabel::Echec(string maReponse) {
  string TempRecord;
  kurz("Mais non! c'était " + maReponse + "\n\n");
}

int Vokabel::CBien(){
  kurz("C'est bien!\n");
  //  reussite(myRandom,KEYINDEX);
}

int Vokabel::NormalMode() {
  result = MonField[STRINGINDEX].compare(reponse);
  if (result==0) {
    CBien();
  } else 
    Echec(MonField[STRINGINDEX]);
}

int Vokabel::questionnaire () {
  myRandom=rand() % str_rcdSET.size();
  
  MonField[KEYINDEX] = str_rcdSET[myRandom][str_rcdSET.questionIndex.back()];
  MonField[STRINGINDEX] = str_rcdSET[myRandom][str_rcdSET.reponseIndex.back()];

    kurz("------------------------------------------------\n");
    kurz(MonField[KEYINDEX]+"\n");

    invite();

    NormalMode();

    return true;
}

int Vokabel::isFullySetVector() {
    for (int i=0; i<str_rcdSET.size();i++)
      if ( fautIlRedemander (i, str_rcdSET.questionIndex.back() ))
	return false;
    return true;
}

