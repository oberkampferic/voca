#include "pedagogie.hpp"

pedagogie::pedagogie(int argc, char *argv[]): Vokabel(argc, argv) {
  kurz("Initialisation=================================================\n");

  string current_exec_name = argv[0];
  string first_arge;

//  string second_arge;
//  vector<string> all_args;

//  if (argc == 1) {
//    cout << "MENU GÉNÉRAL: OPTIONS DISPONIBLES" << endl;
//    cout << "0: Vocabulaire général" << endl;
//    cout << "A: Grammaire Conjugaison Vocabulaire" << endl;
//    cout << "B: Theme" << endl;
//    cout << "C: Version" << endl;
//    cout << "D: Civilisation" << endl;
//    cout << "E: Littérature allemande après 45" << endl;
//    cout << "W: Alf" << endl;
//    cout << "X: Textes et images" << endl;
//    cout << "Y: Littérature XVIII-XIX" << endl;
//    cout << "Z: Grand repères" << endl;
//    
//    Hauptantwort = getchar();
//
//    switch( Hauptantwort) {
//    case '0'://###########################################################
//      cout << "Vocabulaires: tout" << endl;
//      pedagogieLoadFile("../../0-Bdd/0-Général/adverbesEtConjonctionInterro",            &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/AssimilAppris",                           &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/Assimil",                                 &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/VerbeFortsCat2",                          &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/aApprendreGenre",                         &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/ilResteAApprendre3",                      &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/ilResteAApprendre4",                      &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/ilResteAApprendre5",                      &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/0-Général/mythosOpfer",                             &monTriptyshRecordSet);
//      pedagogieLoadFile("../../0-Bdd/E/DeutschLitteratur",                               &monTriptyshRecordSet);
//      pedagogieLoadFile("../../../Nanterre/S1/LittératureSuisse/LitteratureVocaAuteurs", &monTriptyshRecordSet);
//      //      monTriptyshRecordSet.stringR.sort(0);
//
//      //----------------------------------------
//      //      pedagogieLoadFile("../../0-Bdd/0-Général/Aintégrer/häufigstenWorte",               &monTriptyshRecordSetHauftig);
//      //pedagogieLoadFile("../../0-Bdd/0-Général/Aintégrer/Dico",                          &monTriptyshRecordSetDico);
//
//      //----------------------------------------
//      //      monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/0-Général/0-Tout"); // pour la sauvegarde
//      return;	break;
//      
//    case 'A'://###########################################################
//      cout << "a: Verbes Forts: connaissance des verbes: partie a" << endl;
//      cout << "b: Verbes Forts: connaissance des verbes: partie b" << endl;
//      cout << "c: Verbes Forts: connaissance des verbes: partie c" << endl;
//      cout << "d: Verbes Forts: Tout à la fois" << endl;
//      cout << "e: Verbes Forts: connaissance des flexions: partie a" << endl;
//      cout << "f: Verbes Forts: connaissance des flexions: partie b" << endl;
//      cout << "g: conjugaison test général" << endl << endl;
//    
//      Hauptantwort = getchar();
//      Hauptantwort = getchar();
//    
//      switch( Hauptantwort) {
//      case 'a': monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/A/VerbesFortsParta");     break;
//      case 'b': monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/A/VerbesFortsPartb"); 	 break;
//      case 'c': monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/A/VerbesFortsPartc"); 	 break;
//      case 'd':
//	pedagogieLoadFile("../../0-Bdd/A/VerbesFortsParta", &monTriptyshRecordSet);
//	pedagogieLoadFile("../../0-Bdd/A/VerbesFortsPartb", &monTriptyshRecordSet);
//	pedagogieLoadFile("../../0-Bdd/A/VerbesFortsPartc", &monTriptyshRecordSet);
//	monTriptyshRecordSet.stringR.fileName.assign      ("../../0-Bdd/A/VerbesFortsPartd"); // pour la sauvegarde
//	return;	break;
//      case 'e': monTriptyshRecordSet.stringR.fileName.assign("");				 break;
//      case 'f': monTriptyshRecordSet.stringR.fileName.assign("");				 break;
//      case 'g': monTriptyshRecordSet.stringR.fileName.assign("");				 break;
//      default:   erreur ("pedagogie", "pedagogie", "mauvaise saisie"); break;
//      } break;
//    case 'E'://###########################################################
//      monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/E/DeutschLitteratur");
//      pedagogieLoadFile(monTriptyshRecordSet.stringR.fileName, &monTriptyshRecordSet);
//      return; break;
//    case 'W'://###########################################################
//      monTriptyshRecordSet.stringR.fileName.assign("../../0-Bdd/W/Alf");
//      pedagogieLoadFile(monTriptyshRecordSet.stringR.fileName, &monTriptyshRecordSet);
//      return; break;
//      
//    default: erreur ("pedagogie", "pedagogie", "mauvaise saisie"); break;
//    }
//  }
//
//   else
  /*temp*/ 
  if (argc==1) {
    cout << "Usage: " << argv[0] << " <nomFichier>" << endl;
    exit(0);
  }
  /*~temp*/
  
    if (argc > 1) {
    first_arge = argv[1];
//    monTriptyshRecordSet.stringR.fileName = argv[1];
//  all_args.assign(argv+1, argv + argc);

//    if (argc > 2) 
//      for (int i=2; i<argc; i++) {
//	second_arge = argv[i];
//	debug ("pedagogie", "pedagogie", "second_arge: " + second_arge);
//	//----------------------------------------
//	if (second_arge.compare(0, 2, "DI")==0){
//	  if ((i+2) > argc) 
//	    erreur("pedagogie", "pedagogie", "Nombres d'arguments insuffisant ");
//	  istringstream ss(argv[i+1]);
//	  if (!(ss >> maTriTable.stringR.flagCount)) {
//	    debug("pedagogie", "pedagogie", "Invalid number ");
//	    erreur("pedagogie", "pedagogie", argv[1]);
//	  }
//	}
//	//----------------------------------------
//	if (second_arge.compare(0, 4, "MEMN")==0) this->bascule(&maTriTable.stringR.flagMemo);
//	if (second_arge.compare(0, 4, "MEMH")==0) this->bascule(&maTriTable.stringR.flagMemo);
//      }
//    debug("pedagogie", "pedagogie", all_args[0]);
  }


    //  string nomFichier(maTriTable.stringR.fileName);
  //  if (nomFichier.substr(nomFichier.length()-4,nomFichier.length()).compare(0,4,"save") == 0) flagSuperStatic=true;
    //pedagogieLoadFile(argv[1]);
    
    loadFile(argv[1]);    //        pedagogieLoadFile(maTriTable.stringR.fileName, &maTriTable);
    
  //  maTriTable.stringR.sort(0);
  //  if(flagVerbose);
    maTriTable.stringR.print();
}

int pedagogie::Hauptmenu(){
  interrogation();
}

pedagogie::~pedagogie(){
}
