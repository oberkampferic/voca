#include <sstream>
#include <string>
#include <vector>


#include "../../lib/gründ/preParser.hpp"
//#include "lego.hpp" 

class fichier: public TABLE, public preParser {
public:
  int loadFichier(string fileName);
  int loadRecord (string * contenuFichier, string *fileName,
		  size_t * pos1, size_t * pos2, size_t * pos3);
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
      
  size_t pos1=0, pos2=0, pos3=0;
  int ret;
  for(;;) {
    ret=loadRecord (&contenuFichier, &fileName, &pos1, &pos2, &pos3);
    if (ret==false) return true;
  };
}

int fichier::loadRecord (string * contenuFichier, string *fileName,
			    size_t * pos1, size_t * pos2, size_t * pos3){
  string col;
  RECORD monRecord;

  int valRet=10;
  
  *pos3 = contenuFichier->find("\n", *pos1);
  for (;;) {
    *pos2 = contenuFichier->find("|", *pos1);

    if (*pos2>*pos3) {
      *pos2=*pos3;
      valRet=true;
    }

    if (*pos2==string::npos){
      *pos2=*pos3;
      valRet=false;
    }
	
    col = contenuFichier->substr(*pos1, (*pos2-*pos1));
    monRecord.push_back(col);
    *pos1 = *pos2+1;

    if (valRet!=10){
      add(monRecord); 
      return valRet;
    }
  }
}
