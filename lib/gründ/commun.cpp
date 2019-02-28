#include "commun.hpp"

void commun::bascule (int *flag) {
  if (*flag) *flag=false;
  else *flag=true;
  debug ("main.hpp", "bascule", "état: " + to_string(*flag));
}

int commun::isSetVector(vector<int> coli) {
  for (int i=0; i<coli.size();i++)
    if (coli[i]!=true) return false;
  return true;
}

long commun::monTemps() {
  struct tm y2k = {0};
  long seconds;

  time_t timer;
  time(&timer);
  
  y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
  y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

  time(&timer);  /* get current time; same as: timer = time(NULL)  */
  seconds = difftime(timer,mktime(&y2k));
}
