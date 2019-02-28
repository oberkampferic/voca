#include "openGl.hpp"
#include "openGlWindows.cpp"

void openGlInterface::init_font(GLuint base, char* f) {
  Display* display;
  XFontStruct* font_info;
  int first;
  int last;
  int argc=0;
  char * argv[]={""};
  
  /* Need an X Display before calling any Xlib routines. */
  display = XOpenDisplay(0);
  if (display == 0) {
    cout << "XOpenDisplay() failed.  Exiting.\n";
    exit(-1);
  } 
  else {
 
    /* Load the font. */
    //    font_info = XLoadQueryFont(display, f);
    font_info = XLoadQueryFont(display, "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-3");
//    font_info = XLoadQueryFont(display, "7x13euro");
    //font_info = XLoadQueryFont(display, "-bitstream-courier 10 pitch-medium-r-normal--0-0-0-0-m-0-iso10646-1");
    //font_info = XLoadQueryFont(display, "-misc-fixed-medium-r-normal--10-100-75-75-c-60-iso10646-1");


    if (!font_info) {
      cout << "XLoadQueryFont() failed - Exiting.\n";
      exit(-1);
    }
    else {
      /* Tell GLX which font & glyphs to use. */
      first = font_info->min_char_or_byte2;
      last  = font_info->max_char_or_byte2;
      glXUseXFont(font_info->fid, first, last-first+1, base+first);
    }
    XCloseDisplay(display);
    display = 0;
  }
}

void openGlInterface::print_string(GLuint base, const char* s) {
  if (!glIsList(font_base)) {
    cout << "print_string(): Bad display list. - Exiting.\n";
    exit (-1);
  }
  else if (s && strlen(s)) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(base);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *)s);
    glPopAttrib();
  }
}

void openGlInterface::my_init(char* f) {
  font_base = glGenLists(256);
  if (!glIsList(font_base)) {
    //     cout << "my_init(): Out of display lists. - Exiting.\n";
    exit (-1);
  }
  else {
    init_font(font_base, "fixed");
  }
}

void openGlInterface::my_reshape(int w, int h) {
  GLdouble size;
  GLdouble aspect;

  /* Use the whole window. */
  glViewport(0, 0, w, h);

  /* We are going to do some 2-D orthographic drawing. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  size = (GLdouble)((w >= h) ? w : h) / 2.0;
  if (w <= h) {
    aspect = (GLdouble)h/(GLdouble)w;
    glOrtho(-size, size, -size*aspect, size*aspect, -100000.0, 100000.0);
  }
  else {
    aspect = (GLdouble)w/(GLdouble)h;
    glOrtho(-size*aspect, size*aspect, -size, size, -100000.0, 100000.0);
  }

  /* Make the world and window coordinates coincide so that 1.0 in */
  /* model space equals one pixel in window space.                 */
  glScaled(aspect, aspect, 1.0);

  /* Now determine where to draw things. */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}
void openGlInterface::attente(void) {
  // une variable pour memoriser le temps a attendre
  static int nWaitUntil = glutGet(GLUT_ELAPSED_TIME);

  // on recupere le temps présent
  int nTimer = glutGet(GLUT_ELAPSED_TIME);
  // et on le compare a l'instant qu'il faut attendre
  if(nTimer >= nWaitUntil) {
    // pour rafraichir l'affichage
    glutPostRedisplay();
    // 5 fois pas seconde
    nWaitUntil = nTimer + (1000 / 30);
  }
}

void openGlInterface::my_motionMouse(int x, int y) {
  float delta[2];

  if (leftState==1) {    //déplacement de l'ensemble de la map
    delta[X]=old[X]-x;
    delta[Y]=old[Y]-y;
    pos[X]+=delta[X]/ratio[X];
    pos[Y]-=delta[Y]/ratio[Y];
    old[X]=x; old[Y]=y;
  }
  if (rightState==1) {   //déplacement de la colonne dont
      delta[X]=old[X]-x;
      Bdd[nearestTableIndex].pos[X]-=delta[X]/ratio[X];
      old[X]=x;
  }
}

double carreFunc(double x1) {
  return x1*x1;
}
void openGlInterface::my_mouse(int button, int state, int x, int y) {
  int mod=glutGetModifiers();
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;
  
  switch(button) {
  case GLUT_LEFT_BUTTON: 
    if (state==GLUT_DOWN) {//Enclenchement du déplacement de la map
      leftState=1;
      old[X]=x; old[Y]=y;
    }
    if (state==GLUT_UP) {//Désenclenchement du déplacement de la map
      leftState=0;
    } break;
  case GLUT_RIGHT_BUTTON:
    if (state==GLUT_DOWN) {//Enclenchement du déplacement d'une colonne
      rightState=1;

      long monDeltaX, bestDeltaX;

      for (int i=0; i< Bdd.size(); i++) {
	if ( nearestTableIndex == -1) { //besoin d'initialiser
	  bestDeltaX = carreFunc(Bdd[i].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
	  nearestTableIndex = 0;
	}
	monDeltaX =   carreFunc(Bdd[i].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
	if (monDeltaX<bestDeltaX) {
	  bestDeltaX=monDeltaX;
	  nearestTableIndex = i;
	}
      }
      old[X]=x; old[Y]=y;
    }
    if (state==GLUT_UP) {//Désenclenchement du déplacement d'une colonne
      rightState=0;
      nearestTableIndex=-1;
    }
    break;
  case 3:
      //Zoom
      // Adaptation de posx pour zoomer à partir de la position de la souris
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
      double oldRatiox=ratio[X];
      ratio[X]/= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[X] -= ( ((((double) x - widthSur2 ) /    ratio[X]) + pos[X]) -
                ((((double) x - widthSur2 ) / oldRatiox) + pos[X])              );
    } else {
      double oldRatioy=ratio[Y];
      ratio[Y]/= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[Y] += ( ((((double) y - heightSur2 ) /    ratio[Y]) + pos[Y]) -
		((((double) y - heightSur2 ) / oldRatioy) + pos[Y])              );
    }
    break;
  case 4:
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL){//Dézoomage
      double oldRatiox=ratio[X];
      ratio[X]*= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[X] -= ( ((((double) x - widthSur2 ) /    ratio[X]) + pos[X]) -
                ((((double) x - widthSur2 ) / oldRatiox) + pos[X])              );
    }
    else {
      double oldRatioy=ratio[Y];
      ratio[Y]*= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[Y] += ( ((((double) y - heightSur2 ) /    ratio[Y]) + pos[Y]) -
		((((double) y - heightSur2 ) / oldRatioy) + pos[Y])              );
    }
    break;
  default:
    break;
  }
}

openGlInterface::openGlInterface(int argc, char * argv[]){
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
    
  glutInitWindowSize(800, 700);
  
  glutInit(&argc, argv);
  glutIdleFunc(attente);

  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    
  strcpy(window_title, "glxfont: ");
  strcpy(font_name, "fixed");
  strcat(window_title, font_name);

  glutCreateWindow(window_title);

  my_init(font_name);

  glutReshapeFunc(my_reshape);
  glutMotionFunc(my_motionMouse);
  glutMouseFunc(my_mouse);
}

