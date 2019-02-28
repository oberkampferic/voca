#include "main.hpp"
#include "bergson.hpp"
#include "openGl.hpp"


tableBergson bergson::maTableVide; 
string bergson::s_Categorie;
string bergson::s_Name;   
string bergson::s_Date1;
string bergson::s_Date2;
string bergson::s_Memo;
           
vector<tableBergson> openGlInterface::Bdd;
TABLE                openGlInterface::maListeDeListe;
string               openGlInterface::fileName;
string               openGlInterface::fileNameListe;
float                openGlInterface::pos[]= {0.0 , 0.0};
float                openGlInterface::ratio[]= {1.0, 1.0};
float                openGlInterface::old[]={0.0, 0.0};
float                openGlInterface::offsety=0.0;
int                  openGlInterface::posxCurseur;
int                  openGlInterface::pause=false;
int                  openGlInterface::leftState=0;
int                  openGlInterface::rightState=0;
int                  openGlInterface::nearestTableIndex=-1;
GLuint               openGlInterface::font_base = 0;
int main(int argc, char *argv[]) {
  bergson monbergson(argc, argv);

  glutDisplayFunc(monbergson.interrogation); 
  glutMainLoop();

  return 0;
}

