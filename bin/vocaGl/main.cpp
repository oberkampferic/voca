#include "main.hpp"
#include "openGl.hpp"

int openGlInterface::tastatur=TASTATUR_DEUTSCH;
int openGlInterface::activerAffichage=true;
Uint32 openGlInterface::start_time;
Uint32 openGlInterface::last_time;
Uint32 openGlInterface::current_time;
Uint32 openGlInterface::ellapsed_time;
string openGlInterface::s_Allemand;
string openGlInterface::s_Francais;
           
vector<vector< tableBergson>> openGlInterface::ServerBdd;
TABLE                openGlInterface::maListeDeListe;
TABLE                openGlInterface::monDico;
TABLE                openGlInterface::monHauftisteWorte;
TABLE                openGlInterface::prefixe;
TABLE                openGlInterface::suffixe;
TABLE                openGlInterface::tmpDico;
TABLE                openGlInterface::tmpHauftig;
TABLE                openGlInterface::tmpDicoXhauftig;

string               openGlInterface::fileName;
string               openGlInterface::fileName2;
string               openGlInterface::fileNameListe;

float                openGlInterface::pos[]= {0.0 , 0.0};
float                tableBergsonHead::ratio[]= {1.0, 1.0};
float                openGlInterface::old[]={0.0, 0.0};
float                openGlInterface::offsety=0.0;

int                  openGlInterface::modeEco=false;
int                  openGlInterface::pause=false;
int                  openGlInterface::Kartebewegung=0;
int                  openGlInterface::Spaltebewegung=0;
int                  openGlInterface::Wortreihebewegung=0;
int                  openGlInterface::nearestTableIndex=-1;
int                  openGlInterface::posxCurseur=0;
int                  openGlInterface::posyCurseur=0;
int                  openGlInterface::bddCurseur=0;

unsigned int openGlInterface::indexErstWort;
unsigned int openGlInterface::indexLetztWort;

unsigned int         openGlInterface::einfugemarkefarbe=0;
unsigned int         openGlInterface::einfugemarkewort=0;
GLuint               openGlInterface::font_base=0;
int                  openGlInterface::idFont=1;

int main(int argc, char *argv[]) {
  openGlInterface monbergson(argc, argv);

  glutDisplayFunc(monbergson.interrogation); 
  glutMainLoop();

  return 0;
}

