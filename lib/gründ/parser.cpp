#include "parser.hpp"

int parser::ReplaceString(string * subject, string search, string strReplace) {
  size_t pos;
  
  while ( (pos = subject->find(search, 0)) != subject->npos ) {
    if (pos>subject->length()) return 0;
    while (pos != subject->npos) {
      subject->replace(pos, search.length(), strReplace);
      pos += strReplace.length();
      pos = subject->find(search, pos);
    }
  }
}

int parser::nbSeparateurEnLigne(string * ligne) {
  int i=0;
  size_t pos1 = 0;
  size_t pos2;

  do {
    pos2 = ligne->find("|", pos1);
    if (pos2 == ligne->npos) break;
    pos1 = pos2+1;
    i++;
  } while (true);

  return i;
}

int parser::nbColonneEnLigne(string * ligne) {
  int i = nbSeparateurEnLigne(ligne);
//  debug("parser", "nbColonneEnLigne", to_string(i) + " separateurs");
  return i+1;
}


//########################################
//partie entête

int parser::detectNbColonne(string * contenuFichier){
  //detection du nombre de colonne
  cout << "Detection nb colonne entete=================================" << endl;
  
  string ligne=contenuFichier->substr(0, contenuFichier->find("\n"));
  return nbColonneEnLigne(&ligne);
}

int parser::detectNbColonneInit(string * contenuFichier){
  //detection du nombre de colonne après l'entête
  cout << "Detection nb colonne init===================================" << endl;
  size_t pos;
  pos = contenuFichier->find("\n",0);
  pos++;
  
  string ligne=contenuFichier->substr(pos, contenuFichier->find("\n", pos)-pos);

  cout << ligne << endl;
  cout << nbColonneEnLigne(&ligne);
  
//  debug("parser", "detectNbColonneInit", ligne);
  return nbColonneEnLigne(&ligne);
}


