#ifndef HEAD_HPP
#define HEAD_HPP

#include "commun.hpp"
#include "preParser.hpp"
#include "../interfacetty/interfacetty.hpp"

class head: virtual public commun, public preParser {
public:
  vector<int> reponseIndex;
  vector<int> questionIndex;
  vector<int> memoIndex;
  vector<int> shotIndex;

  int flagMemo=0, flagShot=0;
  unsigned int nbColonnes;

  size_t analyseEntete(string * rawFile);
  int saveEntete(ostream * out);
  int printIndex();
};

#endif
