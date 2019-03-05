#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <cstdlib> //system
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */
#include <math.h>

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

class bddBergsonHead:vector<tableBergsonHead> {
public:
  int flagVisible;
  int flagQuestionVisible;
  int flagMemoVisible;
  double pos[2];
  float color[4];
  string filename;

  static float  ratio[2];

  bddBergsonHead(){
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
  static Uint32 start_time;
  static Uint32 last_time;
  static Uint32 current_time,ellapsed_time;
  //  static SDL_Event event;
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

  static vector<vector<tableBergson >> ServerBdd;
  static TABLE  maListeDeListe;
  static TABLE  monDico;
  static TABLE  monHauftisteWorte;
  static TABLE  prefixe;
  static TABLE  suffixe;
  static TABLE  tmpDico;
  static TABLE  tmpHauftig;
  static TABLE  tmpDicoXhauftig;

  //curseurs pour les menus
  static int posxCurseur;
  static int posyCurseur;
  static unsigned int einfugemarkewort;
  static unsigned int einfugemarkefarbe;
  //curseur pour quelle base de donnée dans le serveur
  static int bddCurseur;
  static GLuint font_base;
  static GLuint font_base2;

  char window_title[256];
  char font_name[256];
  static int activerAffichage;
  static string s_Allemand;
  static string s_Francais;
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
  void static my_motionMousePassive(int x, int y);
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

class farbe: public vector<float> {
  typename vector<float>::iterator it;
public:
  farbe() {
    float meineLeerSchwimmend = 0.0;
    for (int i=0; i<4; i++) this->push_back (meineLeerSchwimmend);
  }
  void print() {
    for (it=this->begin(); it!=this->end(); ++it) cout << *it << endl;
  }
  void print(unsigned int index) { cout << (*(this->begin()+index)); }
  float& operator [](int idx) {
    return vector<float>::data()[idx];
  }

};

class farbeTabelle: public vector<farbe> {
  typename vector<farbe>::iterator it;
public:
  farbe& operator [](int idx) {
    return vector<farbe>::data()[idx];
  }

  farbeTabelle(int taille, unsigned int typeAlgo, float ratio) {
    farbe meineLeereFarbe;
    for (int i=0; i< taille; i++) {
      //      meineLeereFarbe.print();
      switch (typeAlgo%3) {
      case 0:
	meineLeereFarbe[0]=abs( sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) ) );
	meineLeereFarbe[1]=abs( sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) ) );
	meineLeereFarbe[2]=abs( sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) ) );
	break;
      case 1:
	meineLeereFarbe[0]=( 1 + sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) )) / 2;
	meineLeereFarbe[1]=( 1 + sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) )) / 2;
	meineLeereFarbe[2]=( 1 + sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) )) / 2;
	break;
      case 2:
	meineLeereFarbe[0]=( 1 + sin( (((M_PI/3)*0) + ((M_PI / taille) * i ) )*2 )) / 2;
	meineLeereFarbe[1]=( 1 + sin( (((M_PI/3)*1) + ((M_PI / taille) * i ) )*2 )) / 2;
	meineLeereFarbe[2]=( 1 + sin( (((M_PI/3)*2) + ((M_PI / taille) * i ) )*2 )) / 2;
	break;
      }
      meineLeereFarbe[0]*= ratio;
      meineLeereFarbe[1]*= ratio;
      meineLeereFarbe[2]*= ratio;
      
      meineLeereFarbe[3]= 0.5;
      push_back( meineLeereFarbe );
    }
  }
  int print() {
    for (it=this->begin(); it != this->end(); ++it)
      for (unsigned int j=0; j<4; j++)
	cout << "couleur" << "[" << j << "]:" << it->data()[j] << endl;
  }
};

#endif
