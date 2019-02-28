#include "pedagogie.hpp"

pedagogie::pedagogie(int argc, char *argv[]){
  kurz("Initialisation=================================================\n");

  string current_exec_name = argv[0];
  string first_arge;

  if (argc == 2) {
    first_arge = argv[1];
    loadFile(argv[1]);
  } else {
    cout << "Usage: " << argv[0] << " <nomFichier>" << endl;
    exit(0);
  }
}

int pedagogie::Hauptmenu(){
  interrogation();
}

pedagogie::~pedagogie(){
}
