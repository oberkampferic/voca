#ifndef HEAD_HPP
#define HEAD_HPP

#include "commun.hpp"
#include "../preParser/preParser.hpp"
#include "../interfacetty/interfacetty.hpp"

class head: virtual public commun, public preParser {
public:
  vector<int> reponseIndex;
  vector<int> questionIndex;
  vector<int> memoIndex;
  vector<int> shotIndex;

  unsigned int nbColonnes;

  size_t analyseEntete(string * contenuFichier);
  int saveEntete(ostream * out);
  int printIndex();
};

#endif
