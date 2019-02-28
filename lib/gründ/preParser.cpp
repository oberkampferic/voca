#include "preParser.hpp"


int preParser::controleCoherenceFichier(string * contenuFichier, unsigned int nbColonne) {
  cout << "Controle Coherence Fichier========================================" << endl;
  int i;
  size_t posCR, posCR2=0; //CR: Carrier Return

  posCR2 = contenuFichier->find("\n", 0);
  do {
    posCR=posCR2+1;
    posCR2 = contenuFichier->find("\n", posCR);

    string ligne=contenuFichier->substr(posCR, posCR2-posCR);
    i=nbColonneEnLigne(&ligne);

    if (i!=nbColonne) {
      if ((posCR2-contenuFichier->npos)<1) return true;
      return false;
    }
  } while (posCR2 != contenuFichier->npos);

  return true;
}


void preParser::preParsing(string * contenuFichier){
//  cout << "Parsing========================================================" << endl;
//  cout << "" << endl;
  ReplaceString(contenuFichier, "\t", "|");
  ReplaceString(contenuFichier, "_", "|");
  ReplaceString(contenuFichier, "  ", "|");
  ReplaceString(contenuFichier, " |", "|");
  ReplaceString(contenuFichier, "| ", "|");
  ReplaceString(contenuFichier, "||", "|");
  ReplaceString(contenuFichier, "|\n", "\n");
  ReplaceString(contenuFichier, "\n\n","\n");
  //  cout << *contenuFichier << endl;
}

int preParser::postParsing(string * contenuFichier) {
  ReplaceString(contenuFichier, "\n", "|");  
  ReplaceString(contenuFichier, "||", "|"); 
}

int preParser::deleteStrangeCharacters(string * contenuFichier) {
  ReplaceString(contenuFichier, " ", "|");
  ReplaceString(contenuFichier, ",", "");
  ReplaceString(contenuFichier, ";", "");
  ReplaceString(contenuFichier, ":", "");
  ReplaceString(contenuFichier, "", "");
  ReplaceString(contenuFichier, "?", "");
  ReplaceString(contenuFichier, "!", "");
  ReplaceString(contenuFichier, "/", "");
  ReplaceString(contenuFichier, ".", "");
  ReplaceString(contenuFichier, "", "");
  ReplaceString(contenuFichier, "*", "");
  ReplaceString(contenuFichier, "\"", "");
  ReplaceString(contenuFichier, "•", "");
  ReplaceString(contenuFichier, "=", "");
  ReplaceString(contenuFichier, "(", "");
  ReplaceString(contenuFichier, ")", "");
  ReplaceString(contenuFichier, "{", "");
  ReplaceString(contenuFichier, "}", "");
  ReplaceString(contenuFichier, "[", "");
  ReplaceString(contenuFichier, "]", "");
  ReplaceString(contenuFichier, "-", "1");
}

int preParser::deleteNumbers(string * contenuFichier) {
  ReplaceString(contenuFichier, "0", "");
  ReplaceString(contenuFichier, "1", "");
  ReplaceString(contenuFichier, "2", "");
  ReplaceString(contenuFichier, "3", "");
  ReplaceString(contenuFichier, "4", "");
  ReplaceString(contenuFichier, "5", "");
  ReplaceString(contenuFichier, "6", "");
  ReplaceString(contenuFichier, "7", "");
  ReplaceString(contenuFichier, "8", "");
  ReplaceString(contenuFichier, "9", "");
}
