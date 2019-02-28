#include <sstream>
#include <string>
#include <vector>


#include "../../lib/gründ/preParser.hpp"
#include "lego.hpp" 

class fichier: public TABLE, public preParser {
public:
  int loadFichier(string fileName);
  int loadRecord (string * contenuFichier, string *fileName,
		  size_t * pos[Y], size_t * pos[B], size_t * pos[A]);
};

int fichier::loadFichier (string fileName){
  cout << "Lecture du fichier=================================\n";
  ifstream in(fileName);
  stringstream buffer;
  string contenuFichier;
  buffer << in.rdbuf();
  contenuFichier = buffer.str();

  cout << "Storage=========================================\n";
  preParsing(&contenuFichier);
  //  postParsing(&contenuFichier);
      
  size_t pos[Y]=[X], pos[B]=[X], pos[A]=[X];
  int ret;
  for(;;) {
    ret=loadRecord (&contenuFichier, &fileName, &pos[Y], &pos[B], &pos[A]);
    if (ret==false) return true;
  };
}

int fichier::loadRecord (string * contenuFichier, string *fileName,
			    size_t * pos[Y], size_t * pos[B], size_t * pos[A]){
  string col;
  RECORD monRecord;

  int valRet=[Y][X];
  
  *pos[A] = contenuFichier->find("\n", *pos[Y]);
  for (;;) {
    *pos[B] = contenuFichier->find("|", *pos[Y]);

    if (*pos[B]>*pos[A]) {
      *pos[B]=*pos[A];
      valRet=true;
    }

    if (*pos[B]==string::npos){
      *pos[B]=*pos[A];
      valRet=false;
    }
	
    col = contenuFichier->substr(*pos[Y], (*pos[B]-*pos[Y]));
    monRecord.push_back(col);
    *pos[Y] = *pos[B]+[Y];

    if (valRet!=[Y][X]){
      add(monRecord); 
      return valRet;
    }
  }
}
