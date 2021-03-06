#include "Head.hpp"

size_t head::analyseEntete(string * rawFile) {
  size_t pos1, pos2, posCR ;
  int i=0;
  
  nbColonnes=detectNbColonne(rawFile);
  cout << "analyseEntete:" << nbColonnes << endl;
  if (rawFile->substr(0,1).compare("#") == 0) {
    posCR = rawFile->find("\n", 0);
    pos1=1;
    while (pos1<posCR) {
      pos2 = rawFile->find("|", pos1);
      if (pos2>=posCR) pos2 = posCR;

      if ( rawFile->substr(pos1,(pos2-pos1)).compare("STRING") == 0)  { reponseIndex.push_back(i);  cout << "reponse" << i << endl;}
      if ( rawFile->substr(pos1,(pos2-pos1)).compare("KEY") == 0) { questionIndex.push_back(i); cout << "question" << i << endl;}
      if ( rawFile->substr(pos1,(pos2-pos1)).compare("MEMO") == 0)     { memoIndex.push_back(i);	    cout << "memo" << i << endl;}
      if ( rawFile->substr(pos1,(pos2-pos1)).compare("SHOT") == 0)     { shotIndex.push_back(i);     cout << "shot" << i << endl;}
      pos1 = pos2+1; i++;
    }
    if (interfacetty::flagVerbose) printIndex();
  } else {
    interfacetty::erreur ("head", "analyseEntete", "Pas de ligne d'entête");
  }
  return ++posCR;
}

int head::saveEntete(ostream * out) {
  *out << "#";
  for (int i=0; i<(nbColonnes-1); i++) {
    for (int j=0; j<reponseIndex.size(); j++)	 if ( i == reponseIndex[j] )  *out << "STRING"  << "\t";
    for (int j=0; j<questionIndex.size(); j++)   if ( i == questionIndex[j] ) *out << "KEY"  << "\t";
    for (int j=0; j<memoIndex.size(); j++)	 if ( i == memoIndex[j] )     *out << "MEMO"  << "\t";
    for (int j=0; j<shotIndex.size(); j++)	 if ( i == shotIndex[j] )     *out << "SHOT"  << "\t";
  }
  for (int j=0; j<reponseIndex.size(); j++)	 if ((nbColonnes-1) == reponseIndex[j] )  *out << "STRING";
    for (int j=0; j<questionIndex.size(); j++)   if ((nbColonnes-1) == questionIndex[j] ) *out << "KEY";
    for (int j=0; j<memoIndex.size(); j++)	 if ((nbColonnes-1) == memoIndex[j] )     *out << "MEMO";
    for (int j=0; j<shotIndex.size(); j++)	 if ((nbColonnes-1) == shotIndex[j] )     *out << "SHOT";
  *out << "\n";
}

int head::printIndex() {
  interfacetty::message("head", "printIndex", "reponseIndex");
  for (int i=0; i<reponseIndex.size(); i++)  interfacetty::message("head","printIndex",to_string(reponseIndex[i])   );
  interfacetty::message("head", "printIndex", "questionIndex");
  for (int i=0; i<questionIndex.size(); i++) interfacetty::message("head","printIndex", to_string(questionIndex[i]) );
  interfacetty::message("head", "printIndex", "memoIndex");
  for (int i=0; i<memoIndex.size(); i++)     interfacetty::message("head","printIndex", to_string(memoIndex[i])     );
  interfacetty::message("head", "printIndex", "shotIndex");
  for (int i=0; i<shotIndex.size(); i++)     interfacetty::message("head","printIndex", to_string(shotIndex[i])     );
}

