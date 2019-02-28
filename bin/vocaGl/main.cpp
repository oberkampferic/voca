#include "main.hpp"
//#include "bergson.hpp"
#include "openGl.hpp"


//tableBergson openGlInterface::maTableVide; 
string openGlInterface::s_Allemand;
string openGlInterface::s_Francais;
           
vector<tableBergson> openGlInterface::Bdd;
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
int                  openGlInterface::pause=false;
int                  openGlInterface::leftState=0;
int                  openGlInterface::rightState=0;
int                  openGlInterface::nearestTableIndex=-1;
int                  openGlInterface::posxCurseur;
GLuint               openGlInterface::font_base = 0;

int main(int argc, char *argv[]) {
  openGlInterface monbergson(argc, argv);

  glutDisplayFunc(monbergson.interrogation); 
  glutMainLoop();

  return 0;
}

