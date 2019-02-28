#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <cstdlib>

#include "master.hpp"

using namespace std;

int main(void) {
  master monMaitre;
  
  for(;;) monMaitre.questionnaire();
}
