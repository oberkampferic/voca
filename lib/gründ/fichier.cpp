#include "fichier.hpp"

int fichier::loadHumainSubLoadFichier1 (string * fileName, string * rawFile){
  cout << "Lecture du fichier=================================\n";
  ifstream in(*fileName);
  stringstream buffer;
  buffer << in.rdbuf();
  *rawFile = buffer.str();
  preParsing(rawFile);
  return true;
}

int fichier::loadHumainSubLoadFichier2 (string * fileName, string * rawFile){
  cout << "Storage=========================================\n";
  size_t pos1=0, pos2=0, pos3=0;
  int ret;
  for(;;) {
    ret=loadRecord (fileName, rawFile, &pos1, &pos2, &pos3);
    if (ret==false) return true;
  };
}

int fichier::loadRecord (string *fileName, string * rawFile, 
			    size_t * pos1, size_t * pos2, size_t * pos3){
  string col;
  RECORD monRecord;

  int valRet=10;
  
  *pos3 = rawFile->find("\n", *pos1);
  for (;;) {
    *pos2 = rawFile->find("|", *pos1);

    if (*pos2>*pos3) {
      *pos2=*pos3;
      valRet=true;
    }
    if (*pos2==string::npos){
      *pos2=*pos3;
      valRet=false; //là c la fin
    }
    if ((*pos2==string::npos) && (*pos3==string::npos)) {
      valRet=false;
      return valRet;
    }
    col = rawFile->substr(*pos1, (*pos2-*pos1));
    monRecord.push_back(col);
    *pos1 = *pos2+1;

    if (valRet!=10){
      add(monRecord); 
      return valRet;
    }
  }
}

//########################################

int fichier::loadFichierEntete (string fileName){
  string rawFile;
  loadHumainSubLoadFichier1(&fileName, &rawFile);
  analyseEntete(&rawFile);
  return loadHumainSubLoadFichier2(&fileName, &rawFile);
}

int fichier::loadFichier (string fileName){
  string rawFile;
  loadHumainSubLoadFichier1(&fileName, &rawFile);
  return loadHumainSubLoadFichier2(&fileName, &rawFile);
}

