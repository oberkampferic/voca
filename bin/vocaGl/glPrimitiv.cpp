#include "../../lib/gründ/parser.hpp"
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

void glPrimitiv::print_string(float x, float y, GLuint font_base, string * s) {
  parser MonParser;
  string test;
  unsigned char c;

  glRasterPos2f( x,y);
  c=220; test=c; MonParser.ReplaceString (s, "Ü", test);
  c=220; test=c; MonParser.ReplaceString (s, "ü", test);
  c=214; test=c; MonParser.ReplaceString (s, "Ö", test);
  c=214; test=c; MonParser.ReplaceString (s, "ö", test);
  c=196; test=c; MonParser.ReplaceString (s, "Ä", test);
  c=196; test=c; MonParser.ReplaceString (s, "ä", test);
  c=223; test=c; MonParser.ReplaceString (s, "ß", test);
  
  c=201; test=c; MonParser.ReplaceString (s, "é", test);
  c=200; test=c; MonParser.ReplaceString (s, "è", test);
  c=202; test=c; MonParser.ReplaceString (s, "ê", test);
  c=224; test=c; MonParser.ReplaceString (s, "à", test);
  c=199; test=c; MonParser.ReplaceString (s, "ç", test);
  

  if (!glIsList(font_base)) {
    cout << "print_string(): Bad display list. - Exiting.\n";
    exit (-1);
  }

  else if (s && s->length()) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(font_base);
    glCallLists(s->length(), GL_UNSIGNED_BYTE, (GLubyte *)s->c_str());
    glPopAttrib();
  }
}

