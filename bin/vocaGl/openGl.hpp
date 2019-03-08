#ifndef OPENGL_HPP
#define OPENGL_HPP

#define TASTATUR_DEUTSCH 0
#define TASTATUR_FRANCAIS 1
#define RECHTS 0
#define LINKS 1

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdlib> //system
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */

#include "../../lib/gründ/commun.hpp"
#include "../../lib/gründ/fichier.hpp"
#include "glPrimitiv.hpp"
#include "farbe.hpp"

#define X 0
#define Y 1
#define R 0
#define G 1
#define B 2
#define A 3

using namespace std;

//############################################################

class tableVocaHead {
public:
  int flagVisible;
  int flagQuestionVisible;
  int flagMemoVisible;
  double pos[2];
  float color[4];
  string filename;
  static float ratio[2];

  tableVocaHead();
};

//############################################################
//table muni de son descripteur
//vectorisé et elevé au carré,
//contient l'ensemble des descripteurs du binaire

class tableVoca: public tableVocaHead, public TABLE {
public:
    tableVoca(): tableVocaHead(){};
};

//############################################################

class openGlInterface: public glPrimitiv, public tableVocaHead{
public:
  int flagShot=false, flagBlitz=true;
  static int tastatur;
  static Uint32 start_time, last_time, current_time, ellapsed_time;
  static string fileName, fileName2, fileNameListe;

  static float  pos[2];
  //  static float  ratio[2];
  static float  old[2];
  static float  offsety;

  //Flags----------------------------------------
  static int    modeEco;
  static int    pause;
  static int    Kartebewegung, Spaltebewegung, Wortreihebewegung;
  static int activerAffichage;

  //Index
  static int    nachsteTabelleAmLinks, nachsteTabelleAmRechts;
  static int    nearestTableIndex; //le y est le plus proche

  static unsigned int indexErstWort,  indexLetztWort;
  
  static vector<vector<tableVoca >> ServerBdd;
  static TABLE  maListeDeListe;
  static TABLE  monDico, monHauftisteWorte;
  static TABLE  tmpDico, tmpHauftig;
  static TABLE  tmpDicoXhauftig;
  static TABLE  prefixe, suffixe;

  //curseurs pour les menus
  static int posxCurseur, posyCurseur;
  static unsigned int einfugemarkewort;
  static unsigned int einfugemarkefarbe;
  
  //curseur pour quelle base de donnée dans le serveur
  static int bddCurseur;

  static GLuint font_base, font_base2;

  char window_title[256];
  char font_name[256];

  static string s_Allemand, s_Francais;
  static int idFont;

  //## QUINCAILLERIE #########################################
  void static init_font(GLuint base, char* f, int idFont);
  //## ELEMENTS WINDOWS ######################################
  void static gestionListe_gestionCurseurX(int Sens);
  void static gestionListe_gestionCurseurY(int Sens);
  void static gestionListe_affichageMenuHorizontal();
  void static gestionListe_affichageMenuVertical();
  //## GESTION INTERFACE SOURIS ##############################
  void static colonneConcernee(int x, int y);
  void static wortVerlagerung(int sens);
  int static motConcerne (int x, int y);
  int static radical(string &mot, string &radical);
  int static supprimerArticle(string &mot, string &radical);
  int static radical1(string &mot, string &radical);
  int static radical2(string &mot, string &radical);
  double static offsetPositionMondeCurseurSouris_X(double oldRatiox, int x, int y);
  double static offsetPositionMondeCurseurSouris_Y(double oldRatioy, int x, int y);
  //## GESTION INTERFACE CLAVIER ##############################
  void static my_handle_key(unsigned char key, int x, int y);
  //## INITIALISATION ET POINTEUR DE FONCTION ################
  void my_init(char* f);
  void static my_reshape(int w, int h);
  void static my_motionMouse(int x, int y);
  void static my_motionMousePassive(int x, int y);
  void static my_mouse(int button, int state, int x, int y);
  void static afficherListeDessin1();
  void static afficherListeDessin2();
  void static afficherListeTexte();
  void static afficherListe();
  
  void static interrogation();

  int static loadMetaData();
  int static saveMetaData();
  openGlInterface(int argc, char* argv[]);
};

#endif
