#ifndef FICHIER_HPP
#define FICHIER_HPP

#include <sstream>
#include <string>

//#include "../../lib/gründ/preParser.hpp"
//#include "../../lib/gründ/Head.hpp"
#include "lego.hpp" 

//class fichier: public TABLE, public preParser {
class fichier: public TABLE { //public head {
private:
  int loadHumainSubLoadFichier1 (string * fileName, string * rawFile);
  int loadHumainSubLoadFichier2 (string * fileName, string * rawFile);
  int loadRecord (string *fileName, string * rawFile,
		  size_t * pos1, size_t * pos2, size_t * pos3);
public:
  int loadFichierEntete(string fileName);
  int loadFichier(string fileName);
};

#endif 
