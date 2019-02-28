#include "../../../voca/lib/gründ/fichier.hpp"

int main (int argc, char * argv[]) {
  TABLE maTable, maTable2, maTable3, maTable4;
  DATABASE maBase, maBase2, maBase3, maBase4;
  RECORD monRecord, monRecordVide;
  SGBD sgbd1, sgbd2, sgbd3;
  
  maTable4.importDriver("Assimil");
  maBase3.push_back(maTable4);
  maBase3.push_back(maTable4);

  sgbd1.push_back(maBase3);
  sgbd1.push_back(maBase3);
  sgbd1.describeStructure();
  
  cout << "Test ultime:" << endl;
  cout << "------------" << endl;

  sgbd1.saveBinaireDriver("gnia");

  sgbd2.loadBinaireDriver("gnia");
  sgbd2.saveBinaireDriver("gnia");


  sgbd3.loadBinaireDriver("gnia");
  sgbd3.saveBinaireDriver("gnia");

  sgbd3.describeStructure();
    
  return 0; 
}
