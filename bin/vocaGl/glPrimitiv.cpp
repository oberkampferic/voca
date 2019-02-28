#include "glPrimitiv.hpp"

void glPrimitiv::gestionListe_rectangle(double x1, double y1, double x2, double y2) {
  x1-=2; y1+=2; x2+=2; y2-=2;
  glBegin(GL_LINES);{
    glVertex2f(x1, y1 );
    glVertex2f(x1, y2 );
  } glEnd(); glBegin(GL_LINES);{
    glVertex2f(x1, y2 );   
    glVertex2f(x2, y2 );
  } glEnd(); glBegin(GL_LINES);{
    glVertex2f(x2, y2 );
    glVertex2f(x2, y1 );
  } glEnd(); glBegin(GL_LINES);{
    glVertex2f(x2, y1 );
    glVertex2f(x1, y1 );
  }    glEnd();
}

void glPrimitiv::gestionListe_rectanglePlein(double x1, double y1, double x2, double y2) {
  glBegin(GL_QUADS);{
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
  }    glEnd();
}

void glPrimitiv::print_string(GLuint font_base, const char* s) {
  if (!glIsList(font_base)) {
    cout << "print_string(): Bad display list. - Exiting.\n";
    exit (-1);
  }
  else if (s && strlen(s)) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(font_base);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *)s);
    glPopAttrib();
  }
}

