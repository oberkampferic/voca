#ifndef GL_PRIMITIV
#define GL_PRIMITIV

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <X11/Intrinsic.h>    /* Display, Window */
#include <GL/glx.h>           /* GLXContext */

using namespace std;

class glPrimitiv{
public:
  void static gestionListe_rectangle(double x1, double y1, double x2, double y2);
  void static gestionListe_rectanglePlein(double x1, double y1, double x2, double y2);
  //## TYPOGRAPHIE ###########################################
  void static print_string(GLuint font_base, const char* s);

};

#endif
