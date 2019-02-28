#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

class record{
public:
  string col1;  int coli1;
  string col2;  int coli2;
  string colMemo;
};
  
class Vokabel{
  int result=-1;
  int typeQuestionnaire=0,
    flagCount=-1, flagMemo=0, flagMemoHide=0, flagStatic=-1, saveFormat=0;
  string test;
  int alteReponseIndex;
  
  vector<string> col1;
  vector<string> col2;
  vector<string> colMemo;
  vector<int> coli1, coli2;

  vector<Record> recordSet;
  string fileName;
  string test2;
  
  int loadFile(string fileName);
  int parsing();
  int storage();
  int control();
  int questionnaire(vector<string> col1, vector<string> col2, vector<string> colMemn, vector<int>& coli1, int flagMem, int flagHide );
  
public:
  Vokabel(int argc, char *argv[]);
  ~Vokabel();

  int interrogation();
  int saveFile(string fileName);  
};

int Vokabel::loadFile(string fileName){
  cout << "Lecture du fichier=============================================" << endl;
  
  ifstream in(fileName);
  stringstream buffer;
  buffer << in.rdbuf();
  test = buffer.str();
}

int Vokabel::saveFile(string fileName){
  string extension=".save", fullFileName;
  string extensionOrigine= fileName.substr(fileName.size()-5, 5);

  if (extensionOrigine.compare(extension)!=0) 
    fullFileName = fileName + extension;
  else
    fullFileName = fileName;
  
  ofstream out(fullFileName);
  
  stringstream buffer;
  buffer << " ";
  cout << "Sauvegarde du fichier=============================================" << endl;
  for (int i=0; i<col1.size(); i++) {
    out << col1[i] << "\t" << coli1[i] << "\t"
	<< col2[i] << "\t" << coli2[i] << "\t";

    if (flagMemo==1) {
      if (colMemo[i].compare("")==0) colMemo[i]=="NULL";
      out << colMemo[i] << endl;
    }
  }
}
  
int Vokabel::parsing(){
  cout << "Parsing========================================================" << endl;
  test2 = ReplaceString(test, "\t", "|");   test = test2;
  test2 = ReplaceString(test, "_", "|");   test = test2;

  while (test.find("  ")!=string::npos){
    test2 = ReplaceString(test, "  ", "|"); test = test2;
  }
  test2 = ReplaceString(test, " |", "|");   test = test2;
  test2 = ReplaceString(test, "| ", "|");   test = test2;

  while (test.find("||")!=string::npos){
    test2 = ReplaceString(test, "||", "|"); test = test2;
  }
  cout << "affichage parsé en colonnes" << endl;
  
  cout << test << endl;
  
  switch (detectNbColonne(test)) {
  case 2: flagMemo=0; flagStatic=0; break;
  case 3: flagMemo=1; flagStatic=0; break;
  case 4: flagMemo=0; flagStatic=-1; break;
  case 5: flagMemo=1; flagStatic=-1; break;
  }
  
  test2 = ReplaceString(test2, " \n", "\n");  test = test2;
  test2 = ReplaceString(test2, "\n", "|");  test = test2;

  while (test.find("||")!=string::npos) {
    test2 = ReplaceString(test, "||", "|"); test = test2;
  }
  
  cout << "affichage parsé en gros tas" << endl;
  cout << test << endl;
}
  
int Vokabel::storage(){
  cout << "Storage========================================================" << endl;
  cout << "===============================================================" << endl;
  cout << "===============================================================" << endl;
  
  //create variables that will act as "cursors". we'll take everything between them.
  size_t pos1 = 0;
  size_t pos2;

  string str;
  int x=0; 

  do {
    cout << x << " ";
    //######## col1
    pos2 = test.find("|", pos1);
    if (pos2==test.npos) break;
    str = test.substr(pos1, (pos2-pos1));
    if (flagCount==x) break;
    pos1 = pos2+1;
    col1.push_back(str);

    //-------- coli1
    if(flagStatic == -1) {
      pos2 = test.find("|", pos1);
      if (pos2==test.npos) break;
      str = test.substr(pos1, (pos2-pos1));
      if (flagCount==x) break;
      pos1 = pos2+1;
      coli1.push_back(stoi(str));
    }
    else
      coli1.push_back(0);

    //######## col2
    pos2 = test.find("|", pos1);
    if (pos2==test.npos) break;
    str = test.substr(pos1, (pos2-pos1));
    if (flagCount==x) break;
    pos1 = pos2+1;
    col2.push_back(str);

    //-------- coli2
    if(flagStatic == -1) {
      pos2 = test.find("|", pos1);
      if (pos2==test.npos) break;
      str = test.substr(pos1, (pos2-pos1));
      if (flagCount==x) break;
      pos1 = pos2+1;
      coli2.push_back(stoi(str));
    }
    else
      coli2.push_back(0);

    //######## colMemo
    if (flagMemo==1) { //es gibt eine dritte Spalte für die Eselsbrücken
      pos2 = test.find("|", pos1);
      if (pos2==test.npos) break;
      str = test.substr(pos1, (pos2-pos1));
      if (flagCount==x) break;
      pos1 = pos2+1;
      
      colMemo.push_back(str);
    }


    x++;
  } while(-1);
  cout << endl;
}
  
int Vokabel::control() {
  cout << "### CONTROLE DU VECTEUR ########################" << endl;
  for (int i=0; i<col1.size(); i++) {
    cout << col1[i] << "\t" << "|" << "\t" << col2[i];
    if (flagMemo==1) cout << "\t\t\t" << "|" << "\t" << colMemo[i];
    cout << endl;
  }
}

Vokabel::Vokabel(int argc, char *argv[]){
  cout << "Initialisation=================================================" << endl;
  cout << "===============================================================" << endl;
  cout << "===============================================================" << endl;
  
  string current_exec_name = argv[0];
  string first_arge;
  string second_arge;
  vector<string> all_args;

  if (argc == 1) {
    usage (argv[0]); exit(0);
  }
  if (argc > 1) {
    first_arge = argv[1];
    fileName = argv[1];
    all_args.assign(argv+1, argv + argc);

    if (argc > 2) 
      for (int i=2; i<argc; i++) {
	second_arge = argv[i];
	cout << "second_arge: " << second_arge << endl;
	if (second_arge.compare(0, 4, "GAUC")==0) typeQuestionnaire=1;
	if (second_arge.compare(0, 4, "DROI")==0) typeQuestionnaire=2;
	//----------------------------------------
	if (second_arge.compare(0, 2, "DI")==0){
	  if ((i+2) > argc) {
	    cerr << "Nombres d'arguments insuffisant " << endl;
	    exit(0);
	  }
	  istringstream ss(argv[i+1]);
	  if (!(ss >> flagCount)) {
	    cerr << "Invalid number " << argv[1] << '\n';
	    exit(0);
	  }
	}
	//----------------------------------------
	if (second_arge.compare(0, 4, "MEMN")==0) flagMemo=1;
	if (second_arge.compare(0, 4, "MEMH")==0) flagMemoHide=1;
	//----------------------------------------	
	//	if (second_arge.compare(0, 4, "STAT")==0) flagStatic=-1;
      }
  }

  cout << all_args[0] << endl;
    
  loadFile(argv[1]);
  parsing();
  storage();
  control();
}
  
Vokabel::~Vokabel(){}

int Vokabel::interrogation(){
  cout << "interrogation ================================================" << endl;
  
  string reponse;
  int sensQuestionnaire;

  cout << "typeQuestionnaire: " << typeQuestionnaire << endl;
  cout << "flagCount: " << flagCount << endl;

  switch (typeQuestionnaire) {
  case 0:
    int myRandom, sensQuestionnaire;
    for(;;) {
      myRandom = rand() % col1.size();
      sensQuestionnaire = rand() % 2;
      
      if (sensQuestionnaire==0) {
	if(questionnaire(col1, col2, colMemo, coli1, flagMemo, flagMemoHide)==0)
	  exit(0);
      }
      else 
	if(questionnaire(col2, col1, colMemo, coli2, flagMemo, flagMemoHide)==0)
	  exit(0);
    }
  case 1: for (;;) 
      if (questionnaire(col1, col2, colMemo, coli1, flagMemo, flagMemoHide)==0)
	exit(0);
  case 2: for (;;) 
      if (questionnaire(col2, col1, colMemo, coli2, flagMemo, flagMemoHide)==0)
	exit(0);
  }
}

int Vokabel::questionnaire (vector<string> col1, vector<string> col2, vector<string> colMemn, vector<int>& coli1, int flagMem, int flagHide ) {
  string reponse;
  int myRandom = rand() % col1.size();
  int result;

  if (coli1[myRandom]!=-1) {
    cout << col1[myRandom];
    if ((flagHide==0) && (flagMem==1))cout << "\t\t" << "indice: " << colMemn[myRandom];
    cout << endl << "?> ";
    getline(cin, reponse);

    //réponse correspondante à un ordre?
    if (reponse.compare("save")==0) {
      saveFile(fileName);
      cout << "Sauvegarde effectué!" << endl;
      cout << endl << "?> ";
      getline(cin, reponse);
    }
    if(reponse.substr(0,4).compare("memo")==0){
      colMemo[alteReponseIndex]=reponse.substr(5,reponse.size()-6);
      saveFile(fileName);
      cout << endl << "?> ";
      getline(cin, reponse);
    }
    if(reponse.substr(0,4).compare("cor1")==0){
      col1[alteReponseIndex]=reponse.substr(5,reponse.size()-6);
      saveFile(fileName);
      cout << endl << "?> ";
      getline(cin, reponse);
    }
    if(reponse.substr(0,4).compare("cor2")==0){
      col2[alteReponseIndex]=reponse.substr(5,reponse.size()-6);
      saveFile(fileName);
      cout << endl << "?> ";
      getline(cin, reponse);
    }
    if (reponse.compare("exit")==0) {
      cout << "Passez une bonne soiré! (et attention à l'alcool...)" << endl;
      exit(0);
    }

    alteReponseIndex=myRandom;
    //vérification proprement dite de la réponse
    result = col2[myRandom].compare(reponse);
    if (result==0) {
      cout << "C'est bien!" << endl << endl;
      coli1[myRandom]=-1;
      if (isSetVector(coli1)) return 0;
      saveFile(fileName);
    } else {
      cout << "Mais non! c'était " << col2[myRandom] << endl << endl;
      if (flagMem==1) cout << "indice: " << colMemn[myRandom] << endl << endl;
    }
  }
  return 1;
}
