#include "freqFragment.hpp"

bool freqFragment::is_number(const std::string& s) {
  string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

string freqFragment::getFileContent(const std::string& path) {
  std::ifstream file(path);
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return content;
}

int freqFragment::load(string fileName){
  //CHARGEMENT/////////////////////////////////////////
  tampon = getFileContent(fileName);
}

int freqFragment::parsing(){
  //PARSING////////////////////////////////////////////
  monPreParser.preParsing(&tampon);
  monPreParser.postParsing(&tampon);
  //  monPreParser.deleteStrangeCharacters(&tampon);
  monPreParser.ReplaceString(&tampon, "0", "");
  monPreParser.ReplaceString(&tampon, "1", "");
  monPreParser.ReplaceString(&tampon, "2", "");
  monPreParser.ReplaceString(&tampon, "3", "");
  monPreParser.ReplaceString(&tampon, "4", "");
  monPreParser.ReplaceString(&tampon, "5", "");
  monPreParser.ReplaceString(&tampon, "6", "");
  monPreParser.ReplaceString(&tampon, "7", "");
  monPreParser.ReplaceString(&tampon, "8", "");
  monPreParser.ReplaceString(&tampon, "9", "");

  monPreParser.ReplaceString(&tampon, "\t", "|");
  monPreParser.ReplaceString(&tampon, " ", "|");
  monPreParser.ReplaceString(&tampon, ".", "");
  monPreParser.ReplaceString(&tampon, ",", "");
  monPreParser.ReplaceString(&tampon, ";", "");
  monPreParser.ReplaceString(&tampon, ":", "");
  monPreParser.ReplaceString(&tampon, "&", "");
  monPreParser.ReplaceString(&tampon, "?", "");
  monPreParser.ReplaceString(&tampon, "!", "");
  monPreParser.ReplaceString(&tampon, "/", "");
  monPreParser.ReplaceString(&tampon, ".", "");
  monPreParser.ReplaceString(&tampon, "&", "");
  monPreParser.ReplaceString(&tampon, "*", "");
  monPreParser.ReplaceString(&tampon, "\"", "");
  monPreParser.ReplaceString(&tampon, "•", "");
  monPreParser.ReplaceString(&tampon, "=", "");
  monPreParser.ReplaceString(&tampon, "(", "");
  monPreParser.ReplaceString(&tampon, ")", "");
  monPreParser.ReplaceString(&tampon, "{", "");
  monPreParser.ReplaceString(&tampon, "}", "");
  monPreParser.ReplaceString(&tampon, "[", "");
  monPreParser.ReplaceString(&tampon, "]", "");
  monPreParser.ReplaceString(&tampon, "“", "");
  monPreParser.ReplaceString(&tampon, "”", "");
  monPreParser.ReplaceString(&tampon, "–", "");
  monPreParser.ReplaceString(&tampon, "'", "");
  monPreParser.ReplaceString(&tampon, "—", "");

  monPreParser.ReplaceString(&tampon, "|| ", "|");
  
  //  monPreParser.ReplaceString(&tampon, "-", "1");
  monPreParser.ReplaceString(&tampon, "-", "");
}

int freqFragment::store(){
  //CHARGEMENT VECTEUR/////////////////////////////////
  size_t pos1=0, pos2=0;
  string col;
  int flagLast=false;

  do {
    pos2 = tampon.find("|", pos1);
    if (pos2==string::npos) {
      flagLast=true;
      pos2=tampon.size();
    }
    col = tampon.substr(pos1, (pos2-pos1));
    s_record.push_back(col);
    i_record.push_back(1);
    pos1 = pos2+1;
  } while (!flagLast);
}

int freqFragment::sortAlpha(){
  //TRI BULLE DU VECTEUR //////////////////////////////
  for (int i=0; i < s_record.size(); i++)
    for (int j=i; j < s_record.size(); j++) {
      if (s_record[i].compare (s_record[j]) > 0) {
	int i_swap;
	i_swap = i_record[i];
	i_record[i] = i_record[j];
	i_record[j] = i_swap;

	string s_swap;
	s_swap = s_record[i];
	s_record[i] = s_record[j];
	s_record[j] = s_swap;
      }
    }
}

int freqFragment::sortAlphaSchnell(){
  s_record.sort();
}

int freqFragment::regroup() {
  //REGROUPEMENT //////////////////////////////////////
  for (int i=0; i < s_record.size(); i++) {
    //    if ((i%100)==0) cerr << " A: regroupement en cours." << i << ":" << s_record.size() << endl;
    int j=0;
    while ( (s_record[i+1].compare(s_record[i])==0) && ( (i+1)!=s_record.size())) {
//      if ((j%100)==0) {
//	cerr << " A2: regroupement en cours." << j++ << ":" << s_record.size() << endl;
//	cerr << i << " compare avec " << i+1 << " et size=" << s_record.size() << endl;
//      }
      i_record[i]++;
      s_record.erase( s_record.begin()+i+1 );
      i_record.erase( i_record.begin()+i+1 );
    }
    //    if ((i%100)==0) cerr << " B: regroupement en cours." << i << ":" << s_record.size() << endl;
  }
}

int freqFragment::deleteNumber() {
  for (int i=0; i < s_record.size(); i++) {
    while ( is_number(s_record[i+1]) ) {
      s_record.erase( s_record.begin()+i+1 );
      i_record.erase( i_record.begin()+i+1 );
    }
  }
}

int freqFragment::sortNum() {
  //NOUVEAU TRI BULLE DU VECTEUR SELON I //////////////
  for (int i=0; i < i_record.size(); i++)
    for (int j=i; j < i_record.size(); j++) {
      if (i_record[i] > i_record[j]) {
	int i_swap;
	i_swap = i_record[i];
	i_record[i] = i_record[j];
	i_record[j] = i_swap;

	string s_swap;
	s_swap = s_record[i];
	s_record[i] = s_record[j];
	s_record[j] = s_swap;
      }
    }
}

int freqFragment::substract(freqFragment fF_toSubstract) {
  cout << "substract: " << endl;
  for (int i=0; i < s_record.size(); i++){
    int resultat = fF_toSubstract.search ( s_record[i] );
    if ( resultat >= 0)
      erase( i-- );
  }
}

int freqFragment::merge(freqFragment fF_toMerge) {
  for (int i=0; i<fF_toMerge.size(); i++){
    s_record.push_back(fF_toMerge.s_record[i]);
    i_record.push_back(fF_toMerge.i_record[i]);
  }
}

int freqFragment::print() {
  for (int i=0; i< s_record.size(); i++) {
    //    cout << i_record[i] << " : ";
    cout << s_record[i] << endl;
  }
  cout << s_record.size() << " d'éléments.";
}

int freqFragment::lowerCase() {
  for (int i=0; i< s_record.size(); i++) 
    boost::algorithm::to_lower(s_record[i]);
}

int freqFragment::isTerminaison(string mot, string motif) {
  int result;
  
  if ( mot.size() < motif.size() ) return false;
  //cout << mot << ":" << motif << ":" << mot.substr(mot.size()-motif.size(), mot.size()) << endl;

  if (mot.substr(mot.size()-motif.size(), mot.size()).compare(motif)==0) return true;
  return false;
}


int freqFragment::deleteSqTerminaison() {
  for (int i=0; i < s_record.size(); i++){
    //  if (!( isTerminaison ( s_record[i], "en" ))) erase( i-- );
    if (( isTerminaison ( s_record[i], "an" ))) erase( i-- );
    if (( isTerminaison ( s_record[i], "in" ))) erase( i-- );
    if (( isTerminaison ( s_record[i], "on" ))) erase( i-- );
    if (( isTerminaison ( s_record[i], "un" ))) erase( i-- );
    if (( isTerminaison ( s_record[i], "yn" ))) erase( i-- );
    if (!( isTerminaison ( s_record[i], "n" ))) erase( i-- );
    //    cout << s_record.size() << ":" << i << endl;
  }
//  cout << "resultat:" << isTerminaison("fragen", "en") << endl;
//  cout << "resultat:" << isTerminaison("frage", "en") << endl;
}

freqFragment::freqFragment(string fileName) {
  load(fileName);
  parsing();
  store();
  sortAlphaSchnell();
  regroup();
  sortNum();
}

int freqFragment::save(string fileName) {
  s_record.saveHumainDriver(fileName);
}

int freqFragment::traitementDico(string fileName) {
  cerr << "traitementDico: " << fileName << endl;  cerr << " loading."      << endl;
  load(fileName);                                  cerr << " parcing."      << endl;
  parsing();                                       cerr << " storage."      << endl;
  store();                                         cerr << " lowercasage."  << endl;  
  lowerCase();                                     cerr << " tri."          << endl;
  sortAlphaSchnell();                              cerr << " regroupement." << endl;
  regroup();                                       
}
