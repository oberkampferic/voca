#include "table.hpp"

void table::pedagogieLoadFile(string filename, recordSet<string> * myRecordSet) {
  loadFile(filename);
  parsing();
  myRecordSet->nbColonnes = nbColonnes;
  if (!myRecordSet->storage(contenuFichier)) erreur("pedagogie","pedagogieLoadFile", filename + "Problème1.");
}

int table::loadFile(string fileName){
  kurz("Lecture du fichier=============================================\n");
  
  ifstream in(fileName);
  stringstream buffer;
  buffer << in.rdbuf();
  contenuFichier = buffer.str();
}
//true pas de problème
//false problème

int table::parsing(){
  unsigned int monNbColonnes;
  cout << "preparsing" << endl;
  preParsing(&contenuFichier);

  monNbColonnes = detectNbColonneInit(&contenuFichier);
  if (controleCoherenceFichier(&contenuFichier, monNbColonnes)==false) 
    erreur ("table", "parsing", "problème de cohérence, nombre de colonnes." + to_string(monNbColonnes));
  cout << "analyseEntete" << endl;
  size_t pos=analyseEntete(&contenuFichier);
  
  if (memoIndex.size()==0) flagMemo=false; else flagMemo=true;
  flagShot=false;

  contenuFichier=contenuFichier.substr(pos, contenuFichier.npos -pos);
  cout << "postparsing" << endl;
  postParsing(&contenuFichier);
  debug ("table", "parsing",  "contenuFichier:" + contenuFichier);

  nbColonnes=monNbColonnes;
  cout << "fin" << endl;
}




