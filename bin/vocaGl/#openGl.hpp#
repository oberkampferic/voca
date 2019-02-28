#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdlib> //system
#include <GL/gl.h>
#include <GL/glut.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */
#include "../../lib/gründ/commun.hpp"
#include "../../lib/gründ/fichier.hpp"
#include "glPrimitiv.hpp"

#define X 0
#define Y 1
#define R 0
#define G 1
#define B 2
#define A 3

using namespace std;

class tableBergsonHead {
public:
  int flagVisible;
  int flagQuestionVisible;
  int flagMemoVisible;
  double pos[2];
  float color[4];
  string filename;

  static float  ratio[2];

  tableBergsonHead(){
   color[0]=1.0;		     
   color[1]=1.0;		 
   color[2]=0.0;		 
   pos[0]=0.0;		 
   pos[1]=0.0;		 
   flagQuestionVisible=1;	 
   flagMemoVisible=1;	 
   flagVisible=1;		 
   filename.assign("Nouveau");
  }
};

class tableBergson: public tableBergsonHead, public TABLE {
public:
    tableBergson(): tableBergsonHead(){};
};

class openGlInterface: public glPrimitiv, public tableBergsonHead{
public:
  int flagShot=false, flagBlitz=true;
  
  static string fileName;
  static string fileName2;
  static string fileNameListe;
  static float  pos[2];
  //  static float  ratio[2];

  static float  old[2];
  static float  offsety;
  static int    pause;
  static int    leftState, rightState;
  static int    nearestTableIndex; //le y est le plus proche

  static vector<tableBergson > Bdd;
  static TABLE  maListeDeListe;
  static TABLE  monDico;
  static TABLE  monHauftisteWorte;
  static TABLE  prefixe;
  static TABLE  suffixe;
  static TABLE  tmpDico;
  static TABLE  tmpHauftig;
  static TABLE  tmpDicoXhauftig;

  static int posxCurseur;
  static GLuint font_base;

  char window_title[256];
  char font_name[256];

  static string s_Allemand;
  static string s_Francais;

  //## QUINCAILLERIE #########################################
  void static attente (void);
  void init_font(GLuint base, char* f);
  //## ELEMENTS WINDOWS ######################################
  void static gestionListe_gestionCurseur(int Sens);
  void static gestionListe_affichageMenuHorizontal();
  void static gestionListe_affichageMenuVertical();
  //## GESTION INTERFACE SOURIS ##############################
  void static colonneConcernee(int x, int y);
  int static motConcerne (int x, int y);
  int static radical(string &mot, string &radical);
  int static supprimerArticle(string &mot, string &radical);
  int static radical1(string &mot, string &radical);
  int static radical2(string &mot, string &radical);
  double static offsetPositionMondeCurseurSouris_X(double oldRatiox, int x, int y);
  double static offsetPositionMondeCurseurSouris_Y(double oldRatioy, int x, int y);
  //## INITIALISATION ET POINTEUR DE FONCTION ################
  void my_init(char* f);
  void static my_reshape(int w, int h);
  void static my_motionMouse(int x, int y);
  void static my_mouse(int button, int state, int x, int y);
  void static afficherListeDessin1();
  void static afficherListeDessin2();
  void static afficherListeTexte();
  void static afficherListe();
  
  void static interrogation();

  void static my_handle_key(unsigned char key, int x, int y);

  int static loadMetaData();
  int static saveMetaData();
  openGlInterface(int argc, char* argv[]);
};

#endif
