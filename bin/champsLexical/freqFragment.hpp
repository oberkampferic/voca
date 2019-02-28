#include "../../lib/gründ/preParser.hpp"
#include "../../lib/gründ/lego.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <boost/algorithm/string.hpp>

using namespace std;

class freqFragment{
private:
  bool is_number(const std::string& s);
  string getFileContent(const std::string& path);

public:
  preParser monPreParser;
  string tampon;
  RECORD s_record;
  RECORD_I i_record;
  //  --------------------------------------------------
  int size() { return s_record.size(); }
  //  --------------------------------------------------
  int erase(int index) {
    s_record.erase(s_record.begin() + index);
    i_record.erase(i_record.begin() + index);
  }
  //  --------------------------------------------------
  int search( string motif) {
    return search (0, size()/2, size(), motif);
  }
  //  --------------------------------------------------
  int search( int indexDebut, int index, int indexFin, string motif) {
    int result;
    int result2=-1;
    string s_compare="";
    string s_compare2="";
    
    s_compare  = s_record[index];
    
    if ((index+1)!=indexFin)
      s_compare2 = s_record[index+1];
//    boost::algorithm::to_lower(motif);
//    boost::algorithm::to_lower(s_compare);
//    boost::algorithm::to_lower(s_compare2);

    result= s_compare.compare(motif);
    result2= s_compare2.compare(motif);

    if (result==0) return indexDebut;
    if (result2==0) return indexDebut+1;
    
    if (indexFin==indexDebut) return -1;
    if (indexFin==indexDebut+1) return -1;
    
    if (result<0) indexDebut=index; 
    if (result>0) indexFin=index; 

    index = (indexDebut+indexFin)/2;
    return search (indexDebut, index, indexFin, motif);
  }
  //  --------------------------------------------------
  int load(string fileName);
  int parsing();
  int store();
  int sortAlpha();
  int sortAlphaSchnell();
  int regroup();
  int deleteNumber();
  int sortNum();
  int substract(freqFragment fF_toSubstract);
  int merge(freqFragment fF_toMerge);
  int print();
  int save(string fileName);
  int lowerCase();
  int isTerminaison(string mot, string motif);
  int deleteSqTerminaison();
  freqFragment() {};
  freqFragment(string fileName);
  int traitementDico(string fileName);
};
