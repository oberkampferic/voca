#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */
#include "../../lib/gründ/commun.hpp"
#include "../../lib/gründ/fichier.hpp"
#define X 0
#define Y 1
#define R 0
#define G 1
#define B 2
#define A 3

using namespace std;

class tableBergson: public TABLE {
public:
  int flagVisible;
  int flagQuestionVisible;
  int flagMemoVisible;
  double pos[2];
  float color[4];
};

class openGlInterface {
public:
  static string fileName;
  static string fileNameListe;
  static float  pos[2];
  static float  ratio[2];
  static float  old[2];
  static float  offsety;
  	 	 
  static int    pause;
  static int    leftState, rightState;
  static int    nearestTableIndex; //le y est le plus proche
  static int    posxCurseur;

  static vector<tableBergson > Bdd;
  static TABLE  maListeDeListe; 
  
  static GLuint font_base;

  char window_title[256];
  char font_name[256];
  void static attente (void);
  void init_font(GLuint base, char* f);
  // gestion windows
  void static gestionListe_rectangle(double x1, double y1, double x2, double y2);
  void static gestionListe_rectanglePlein(double x1, double y1, double x2, double y2);
  void static gestionListe_gestionCurseur(int Sens);
  void static gestionListe_affichageMenuHorizontal();
  void static gestionListe_affichageMenuVertical();
  
  void static print_string(GLuint base, const char* s);
  void my_init(char* f);
  void static my_reshape(int w, int h);
  //  void static my_handle_key(unsigned char key, int x, int y);
  void static my_motionMouse(int x, int y);
  void static my_mouse(int button, int state, int x, int y);

  int static loadMetaData();
  int static saveMetaData();

  openGlInterface(int argc, char* argv[]);
};

#endif
