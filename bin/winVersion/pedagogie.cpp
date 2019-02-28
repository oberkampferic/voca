#include "pedagogie.hpp"

void pedagogie::fileAppendToRecordSet(string fileName){
  //  fileName.assign("0-Bdd/A/VerbesFortsParta");
  loadFile(fileName);
  parsing();
  if (!storage()) erreur("Vokabel","Vokabel", "Storage: Problème.");
}

int pedagogie::Hauptmenu(char Hauptantwort) {
  switch( Hauptantwort) {
  case '0':
    cout << "Vocabulaires: tout" << endl;
    fileAppendToRecordSet("../../0-Bdd/0-Général/adverbesEtConjonctionInterro");
    fileAppendToRecordSet("../../0-Bdd/0-Général/AssimilAppris");
    fileAppendToRecordSet("../../0-Bdd/0-Général/Assimil");
    fileAppendToRecordSet("../../0-Bdd/0-Général/VerbeFortsCat2");
    fileAppendToRecordSet("../../0-Bdd/0-Général/aApprendreGenre");
    fileAppendToRecordSet("../../0-Bdd/0-Général/ilResteAApprendre3");
    fileAppendToRecordSet("../../0-Bdd/0-Général/ilResteAApprendre4");
    fileAppendToRecordSet("../../0-Bdd/0-Général/ilResteAApprendre5");
    fileAppendToRecordSet("../../0-Bdd/0-Général/mythosOpfer");
    fileAppendToRecordSet("../../0-Bdd/E/DeutschLitteratur");
//    fileAppendToRecordSet("../Nanterre/S1/Littérature Suisse/LitteratureVocaAuteurs");
      
    sort(0);
  //----------------------------------------
    loadFile("../../0-Bdd/0-Général/Aintégrer/häufigstenWorte");
    parsing();
    if (!storageHauftigste()) erreur("Vokabel","Vokabel", "Storage: Problème.");
    //----------------------------------------
    loadFile("../../0-Bdd/0-Général/Aintégrer/Dico");
    parsing();
    if (!storageDico()) erreur("Vokabel","Vokabel", "Storage: Problème.");
    //----------------------------------------
    fileName.assign("../../0-Bdd/0-Général/0-Tout"); // pour la sauvegarde
    return true;
      
  case 'A':
    cout << "a: Verbes Forts: connaissance des verbes: partie a" << endl;
    cout << "b: Verbes Forts: connaissance des verbes: partie b" << endl;
    cout << "c: Verbes Forts: connaissance des verbes: partie c" << endl;
    cout << "d: Verbes Forts: Tout à la fois" << endl;
    cout << "e: Verbes Forts: connaissance des flexions: partie a" << endl;
    cout << "f: Verbes Forts: connaissance des flexions: partie b" << endl;
    cout << "g: conjugaison test général" << endl << endl;
    
    Hauptantwort = getchar();
    Hauptantwort = getchar();
    
    switch(Hauptantwort) {
    case 'a': fileName.assign("../../0-Bdd/A/VerbesFortsParta"); return true;
    case 'b': fileName.assign("../../0-Bdd/A/VerbesFortsPartb"); return true;
    case 'c': fileName.assign("../../0-Bdd/A/VerbesFortsPartc"); return true;
    case 'd':
      fileAppendToRecordSet("../../0-Bdd/A/VerbesFortsParta");
      fileAppendToRecordSet("../../0-Bdd/A/VerbesFortsPartb");
      fileAppendToRecordSet("../../0-Bdd/A/VerbesFortsPartc");
      fileName.assign("../../0-Bdd/A/VerbesFortsPartd"); // pour la sauvegarde
      return true;
    case 'e': fileName.assign("");			   return true;
    case 'f': fileName.assign("");			   return true;
    case 'g': fileName.assign("");			   return true;
    default:   erreur ("Vokabel", "Vokabel", "mauvaise saisie"); return true;
    } return true;
  case 'E':
    fileName.assign("../../0-Bdd/E/DeutschLitteratur");
    fileAppendToRecordSet(fileName);
    return true;
  case 'W':
    fileName.assign("../../0-Bdd/W/Alf");
    fileAppendToRecordSet(fileName);
    return true;
      
  default: erreur ("Vokabel", "Vokabel", "mauvaise saisie"); return false;
  }
}

pedagogie::pedagogie(int argc, char *argv[]): Vokabel(argc, argv) {
  kurz("Initialisation=================================================\n");

  string current_exec_name = argv[0];
  string first_arge;
  string second_arge;
  vector<string> all_args;

  if (argc == 1) {

    //    do{
      clear();
      myWindows[0] = subwin(stdscr, 20, 79, 0, 0);
      myWindows[1] = NULL;

      mesCouleursWindows();
      
      mvwprintw(myWindows[0], 1,  2, "MENU GÉNÉRAL: OPTIONS DISPONIBLES" );
      mvwprintw(myWindows[0], 2,  2, "0: Vocabulaire général" );
      mvwprintw(myWindows[0], 3,  2, "A: Grammaire Conjugaison Vocabulaire" );
      mvwprintw(myWindows[0], 4,  2, "B: Theme" );
      mvwprintw(myWindows[0], 5,  2, "C: Version" );
      mvwprintw(myWindows[0], 6,  2, "D: Civilisation" );
      mvwprintw(myWindows[0], 7,  2, "E: Littérature allemande après 45" );
      mvwprintw(myWindows[0], 8,  2, "W: Alf" );
      mvwprintw(myWindows[0], 9,  2, "X: Textes et images" );
      mvwprintw(myWindows[0], 10, 2, "Y: Littérature XVIII-XIX" );
      mvwprintw(myWindows[0], 11, 2, "Z: Grand repères" );

      mesCouleursWindows2();
      
      flash(); beep();
        Hauptantwort = getchar();

//        static struct termios oldt, newt;
//  int c;
//  mvwgetstr(myWindows[0], 4, 9, str);  
//  reponse.assign(str);
  
  //    } while(Hauptmenu(str[0]) == false); //Hauptantwort
	//  } while(Hauptmenu(Hauptantwort) == false);
	Hauptmenu(Hauptantwort);

  } else if (argc > 1) {
      first_arge = argv[1];
      fileName = argv[1];
      all_args.assign(argv+1, argv + argc);

      if (argc > 2) 
	for (int i=2; i<argc; i++) {
	  second_arge = argv[i];
	  debug ("Vokabel", "Vokabel", "second_arge: " + second_arge);
	  //----------------------------------------
	  if (second_arge.compare(0, 2, "DI")==0){
	    if ((i+2) > argc) 
	      erreur("Vokabel", "Vokabel", "Nombres d'arguments insuffisant ");
	    istringstream ss(argv[i+1]);
	    if (!(ss >> flagCount)) {
	      debug("Vokabel", "Vokabel", "Invalid number ");
	      erreur("Vokabel", "Vokabel", argv[1]);
	    }
	  }
	  //----------------------------------------
	  if (second_arge.compare(0, 4, "MEMN")==0) bascule(&flagMemo);
	  if (second_arge.compare(0, 4, "MEMH")==0) bascule(&flagMemo);
	}
      debug("Vokabel", "Vokabel", all_args[0]);
    }

    cout << fileName << endl;
    
    loadFile(fileName);
    string nomFichier(fileName);
    if (nomFichier.substr(nomFichier.length()-4,nomFichier.length()).compare(0,4,"save") == 0) flagSuperStatic=true;
  
    parsing();
    if (!storage()) erreur("Vokabel","Vokabel", "Storage: Problème.");
    sort(0);

    if(flagVerbose) print();
  }

  int pedagogie::Hauptmenu(){
    interrogation();
  }

  pedagogie::~pedagogie(){
  }
