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

void openGlInterface::my_init(char* f) {
  font_base = glGenLists(256);
  if (!glIsList(font_base)) exit (-1);
  else  init_font(font_base, "fixed");
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
    glOrtho(-size*aspect, size*aspect, -size, size, -100000.0, 100000.0);s
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
  //    if (glutGetModifiers() & GLUT_ACTIVE_ALT) {
    if (rightState==1) {   //déplacement de la colonne dont
      delta[X]=old[X]-x;
      Bdd[nearestTableIndex].pos[X]-=delta[X]/ratio[X];
      old[X]=x;
    }
    //  }
}

double carreFunc(double x1) {
  return x1*x1;
}

void openGlInterface::colonneConcernee(int x, int y) {
  double monDeltaX, bestDeltaX;
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;

  if (Bdd.size()>0) { //besoin d'initialiser
      bestDeltaX = carreFunc(Bdd[0].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
      nearestTableIndex = 0;
    }
  for (int i=1; i< Bdd.size(); i++) { 
    monDeltaX =    carreFunc(Bdd[i].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
    if (monDeltaX<bestDeltaX) {
      bestDeltaX=monDeltaX;
      nearestTableIndex = i;
    }
  }
}

int openGlInterface::motConcerne(int x, int y) {
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;
  double projY= (((double) y - (double) heightSur2 ) / ratio[Y])- pos[Y];
  projY/=20; 
  if ((projY<Bdd[nearestTableIndex].size()) && (projY>=0))
    return (int) projY;
  else
    return -1;
}

double openGlInterface::offsetPositionMondeCurseurSouris_X(double oldRatiox, int x, int y){
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;
  return  ( ((((double) x - widthSur2 ) /  ratio[X]) + pos[X]) -
	    ((((double) x - widthSur2 ) / oldRatiox) + pos[X])     );
}

double openGlInterface::offsetPositionMondeCurseurSouris_Y(double oldRatioy, int x, int y){
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;
  return  ( ((((double) y - heightSur2 ) /  ratio[Y]) + pos[Y]) -
	    ((((double) y - heightSur2 ) / oldRatioy) + pos[Y])    );
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int openGlInterface::radical(string &mot, string &s_radical) {
  //recherche du radical
  supprimerArticle(mot, s_radical);
  string s_radical2;
  radical1(s_radical, s_radical2);
  cout << "radical sans préfixes: " << s_radical << endl;
  s_radical.assign(s_radical2);
  radical2(s_radical, s_radical2);
  cout << "radical sans suffixes: " << s_radical2 << endl;
  s_radical.assign(s_radical2);
}

int openGlInterface::supprimerArticle(string &mot, string &s_radical) {
  s_radical.assign(mot);
  int tmpPos = mot.find("(");
  if (tmpPos!=string::npos) s_radical.assign ( mot.begin(), mot.begin() + tmpPos);
  cout << "### mot lu:" << s_radical << endl;

  string commandLine(" rm /tmp/Test.wav ; pico2wave --lang de-DE --wave /tmp/Test.wav '" + s_radical + "' ; play /tmp/Test.wav treble 24 bass 0 gain -1 tempo -q -m -s -l 1.0 32.5153 15.1941 13.0061 &");
  std::system(commandLine.c_str());

  boost::algorithm::to_lower(s_radical);

  if (s_radical.find("der ")!=string::npos) s_radical.assign (s_radical.substr(4, s_radical.size()-4));
  if (s_radical.find("die ")!=string::npos) s_radical.assign (s_radical.substr(4, s_radical.size()-4));
  if (s_radical.find("das ")!=string::npos) s_radical.assign (s_radical.substr(4, s_radical.size()-4));
  if (s_radical.find("ein ")!=string::npos) s_radical.assign (s_radical.substr(4, s_radical.size()-4));
  if (s_radical.find("eine ")!=string::npos) s_radical.assign (s_radical.substr(5, s_radical.size()-5));
  if (s_radical.find("sich ")!=string::npos) s_radical.assign (s_radical.substr(5, s_radical.size()-5));
}

int openGlInterface::radical1(string &mot, string &s_radical) {
      //Analyse des préfixes.
  int valRet=false;
  cout << "radical1        : " << s_radical << endl;
  for (int i=0; i<prefixe.size(); i++){
    if (mot.find(prefixe[i][0])==0){
      cout << "préfixes:" << prefixe[i][0] << " " << endl;
      s_radical.assign( mot.substr(prefixe[i][0].size(), mot.size()-prefixe[i][0].size()) );
      cout << "radical1        : " << s_radical << endl;
      //      string s_radical2;                     //réccursivité
      //      radical1( s_radical, s_radical2);
      //      s_radical.assign(s_radical2);
      return true;      
    }
  }
  s_radical.assign(mot);
  return false;
}

int openGlInterface::radical2(string &mot, string &s_radical) {
      //Analyse des suffixes.
  int valRet=false;
  cout << "radical2        : " << s_radical << endl;
  for (int i=0; i<suffixe.size(); i++){
    if (mot.find(suffixe[i][0], mot.size()-suffixe[i][0].size()-1)!=string::npos){
      cout << "suffixes:" << suffixe[i][0] << " " << endl;
      s_radical.assign( mot.substr(0,
				   mot.size() - suffixe[i][0].size()
				   ));

      cout << "radical2        : " << s_radical << endl;
      //      string s_radical2;                     //réccursivité
      //      radical2( s_radical, s_radical2);
      //      s_radical.assign(s_radical2);
      return true;      
    }
  }
  s_radical.assign(mot);
  return false;
}

void openGlInterface::my_mouse(int button, int state, int x, int y) {
  string s_radical;
  int mod=glutGetModifiers();
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;
  int prochaineTableIndex;
  colonneConcernee(x, y);
  int projY=motConcerne(x,y);	//Identifier quel est le mot le plus proche.

  //recherche Dico de ce mot
  if (state==GLUT_DOWN){
    if (projY!=-1) {  //Il y a bien un mot concerné? 
      cout << Bdd[nearestTableIndex][(int) projY][0] << " <=> "
	   << Bdd[nearestTableIndex][(int) projY][1] << "##################" << endl;

      //### PARTIE RECHERCHE DU RADICAL ############################################
      radical(Bdd[nearestTableIndex][(int) projY][0], s_radical);
      cout << "radical: " << s_radical << endl;

      string tampon;
      //recherche des mots apparentés
      tmpDico.clear();
      if(s_radical.size()>2) { //éviter l'amballement avec les radicaux de une lettre
	for (int i=0; i<monDico.size(); i++) {
	  tampon=monDico[i][0];
	  boost::algorithm::to_lower(tampon);

	  if ( tampon.find( s_radical ) != string::npos ){
	    cout << "Dico:" << monDico[i][0]
		 << ":"     << monDico[i][1] << endl;
	    RECORD  temp;
	    temp.push_back( monDico[i][0] );
	    temp.push_back( monDico[i][1] );
	    tmpDico.push_back(temp);
	  }
	}
	tmpDicoXhauftig.clear();
	tmpHauftig.clear();
	for (int i=0; i<monHauftisteWorte.size(); i++) {
	  tampon=monHauftisteWorte[i][0];
	  boost::algorithm::to_lower(tampon);
	  if (tampon.find( s_radical )  != string::npos){
	    cout << "Häuftig:" << monHauftisteWorte[i][1]
		 << ": "       << monHauftisteWorte[i][0] << endl;
	    RECORD  temp;
	    temp.push_back(monHauftisteWorte[i][0]);
	    temp.push_back(monHauftisteWorte[i][1]);
	    tmpHauftig.push_back(temp);
	    RECORD  temp2;
	    for (int j=0; j<tmpDico.size(); j++) {
	      if (tmpDico[j][0].compare(temp[0])==0) {
		temp2.push_back(tmpDico[j][0]);
		temp2.push_back(tmpDico[j][1]);
		tmpDicoXhauftig.push_back(temp2);
	      }
	    }
	  }
	}
      }
    }
  }
  //### ~PARTIE RECHERCHE DU RADICAL ###########################################


  
  switch(button) {
  case GLUT_LEFT_BUTTON: //########################################
    if (state==GLUT_UP) //Désenclenchement du déplacement de la map
      leftState=0;
    if (state==GLUT_DOWN) {
      if (!(glutGetModifiers() & GLUT_ACTIVE_ALT)) {    //Déplacement d'un mot
	if (projY!=-1) {  //Il y a bien un mot concerné?
	  //Identifier quelle est la colonne de destination
	  if (Bdd.size()>1) { //une seule table?
	    if (nearestTableIndex == 0)       prochaineTableIndex=  (Bdd.size()-1);
	    else                   	    prochaineTableIndex = nearestTableIndex-1;
	    Bdd[prochaineTableIndex].push_back( Bdd[nearestTableIndex][(int) projY] );
	    Bdd[nearestTableIndex].erase(Bdd[nearestTableIndex].begin()+(int) projY);
	  } } }
      leftState=1;         //Enclenchement du déplacement de la map
      old[X]=x; old[Y]=y;
    }
    break;
    
  case GLUT_RIGHT_BUTTON://########################################
    if (state==GLUT_UP) //Désenclenchement du déplacement d'une colonne
      rightState=0;
    if (state==GLUT_DOWN) {
        if (!(glutGetModifiers() & GLUT_ACTIVE_ALT)) {      //Déplacement d'un mot
	  if (projY!=-1) { // il y a bien un mot concerné?
	    //Identifier quelle est la colonne de destination
	    if (Bdd.size()>1) { //une seule table?
	      if ((nearestTableIndex) < (Bdd.size()-1)) prochaineTableIndex = nearestTableIndex+1;
	      else                            	    prochaineTableIndex = 0;
	      Bdd[prochaineTableIndex].push_back( Bdd[nearestTableIndex][(int) projY] );
	      Bdd[nearestTableIndex].erase(Bdd[nearestTableIndex].begin()+(int) projY);
	    } } }
	rightState=1;     //Enclenchement du déplacement d'une colonne
    }
    old[X]=x; old[Y]=y;
    break;

  case 3://####################################################
    //Zoom
    // Adaptation de posx pour zoomer à partir de la position de la souris
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL) {
      double oldRatiox=ratio[X];
      
      ratio[X]/= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[X] -= offsetPositionMondeCurseurSouris_X( oldRatiox, x, y );
    } else {
      double oldRatioy=ratio[Y];
      ratio[Y]/= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[Y] += offsetPositionMondeCurseurSouris_Y( oldRatioy, x, y );
    }
    break;
  case 4://######################################################
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL){//Dézoomage
      double oldRatiox=ratio[X];
      ratio[X]*= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[X] -= offsetPositionMondeCurseurSouris_X( oldRatiox, x, y);
    }
    else {
      double oldRatioy=ratio[Y];
      ratio[Y]*= ((glutGetModifiers() & GLUT_ACTIVE_SHIFT)?0.97:0.8);
      pos[Y] += offsetPositionMondeCurseurSouris_Y( oldRatioy, x, y);
    }
    break;
  default:
    break;
  }
}
  
openGlInterface::openGlInterface(int argc, char * argv[]){
    //C'est ici que l'on s'occupe du chargement des fichiers.
  if (argc!=2) {
    cout << "usage: " << argv[0]
	 << " [fichier.lst | fichier.bin | fichier.txt]" << endl;
  }
  //récupérer l'extension
  string nomFichier(argv[1]);
  string extension = nomFichier.substr(nomFichier.length()-4, nomFichier.length()-1);
  cout << extension << endl;
  cout << nomFichier << endl;
  posxCurseur=0;

  //pour la sauvegarde binaire
  fileName = argv[1];
  
  //## fichier isolé #######################################
  if (extension.compare(".txt")==0){
    tableBergson maTableVide;
    Bdd.push_back(maTableVide);
    Bdd.back().importDriver(nomFichier);
    Bdd[0].filename.assign(nomFichier);
    Bdd[0].color[R]            = 0.0;
    Bdd[0].color[G]	         = 1.0;
    Bdd[0].color[B]	         = 1.0;
    Bdd[0].color[A]            = 1.0;
    Bdd[0].pos[X]	         = 0.0;
    Bdd[0].flagVisible         = 1;
    Bdd[0].flagQuestionVisible = 1;
    Bdd[0].flagMemoVisible     = 1;

//  ofstream tmpOut("cronimousHumain.txt");
//  Bdd[0].saveHumain(&tmpOut);
//  tmpOut.close();
  }
  //## liste de fichiers ###################################
  else   if (extension.compare(".lst")==0){
    fileNameListe.assign(nomFichier);
    maListeDeListe.importDriver(nomFichier);
    
    for (int i=0; i < maListeDeListe.size(); i++) {
      tableBergson maTableVide;
      Bdd.push_back(maTableVide);
      Bdd.back().importDriver(maListeDeListe[i][0]);
      Bdd[i].filename.assign(maListeDeListe[i][0]);
      Bdd[i].color[R]            = stof(maListeDeListe[i][1]);
      Bdd[i].color[G]	       = stof(maListeDeListe[i][2]);
      Bdd[i].color[B]	       = stof(maListeDeListe[i][3]);
      Bdd[i].color[A]            = stof(maListeDeListe[i][4]);
      Bdd[i].pos[X]	       = stod(maListeDeListe[i][5]);
      Bdd[i].flagVisible         = stoi(maListeDeListe[i][6]);
      Bdd[i].flagQuestionVisible = stoi(maListeDeListe[i][7]);
      Bdd[i].flagMemoVisible     = stoi(maListeDeListe[i][8]);
    }
  }
  //## fichier binaire #####################################
  else   if (extension.compare(".bin")==0){
    loadMetaData();
  }
  //########################################################

  //pour la sauvegarde binaire.
  // Attention, loadMetaData se sert de ce nom.
  fileName = fileName + ".save";

  //  monDico.importDriver          ("listes/dico.txt");
  monDico.importDriver          ("listes/cronimousHumain3.txt");
  monHauftisteWorte.importDriver("listes/haufigstenWorte.txt");
  monHauftisteWorte.importDriver("listes/dico.txt");
  prefixe.importDriver          ("listes/prefixe.txt");
  suffixe.importDriver          ("listes/suffixes.txt");
  


  
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
  glutKeyboardFunc(my_handle_key);
}

//double openGlInterface::monX(double offset) { return (Bdd[j].pos[X] + offset - pos[X] ) * ratio[X] };
	  

void openGlInterface::afficherListeDessin1(){
  double ratioCoul=0.1;
  for (int j=0; j <Bdd.size(); j++) {
    for (int i=0; i< Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Carré vertical #################################################
	if (j==posxCurseur)
	  if (ratioCoul < 0.6) ratioCoul=0.8; else ratioCoul=0.3;
	else
	  if (ratioCoul < 0.6) ratioCoul=0.7; else ratioCoul=0.4;
	
	glColor4f( (Bdd[j].color[R] * ratioCoul) / 3,
		   (Bdd[j].color[G] * ratioCoul) / 3,
		   (Bdd[j].color[B] * ratioCoul) / 3,
		   Bdd[j].color[A] * 0.2 );
		
	glColor4f( (Bdd[j].color[R] * ratioCoul) / 3,
		   (Bdd[j].color[G] * ratioCoul) / 3,
		   (Bdd[j].color[B] * ratioCoul) / 3,
		   Bdd[j].color[A] * 0.2 );
	glBegin(GL_QUADS);{
	  glVertex2f( (Bdd[j].pos[X] + 010 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	  glVertex2f( (Bdd[j].pos[X] + 600 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );      
	  glVertex2f( (Bdd[j].pos[X] + 600 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	  glVertex2f( (Bdd[j].pos[X] + 010 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	}    glEnd();
	//## CarréDate ###########################################################
	glColor4f(Bdd[j].color[R] * ratioCoul  , Bdd[j].color[G] * ratioCoul , Bdd[j].color[B] * ratioCoul , Bdd[j].color[A] *0.5);
	glBegin(GL_QUADS);{
	  glVertex2f( (Bdd[j].pos[X] - 10 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f( (Bdd[j].pos[X] - 80 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);      
	  glVertex2f( (Bdd[j].pos[X] - 80 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f( (Bdd[j].pos[X] - 10 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
	
      } } }
}

void openGlInterface::afficherListeDessin2(){
  double ratioCoul=1;

  for (int j=0; j <Bdd.size(); j++) {
    for (int i=0; i< Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Ligne horizontale Date 1#############################################
	glColor4f(Bdd[j].color[R] * 0.5, Bdd[j].color[G] *0.5, Bdd[j].color[B] *0.5, Bdd[j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
	//## Ligne horizontale Date 2#############################################
	glColor4f(Bdd[j].color[R]* 0.2 , Bdd[j].color[G]* 0.2 , Bdd[j].color[B]* 0.2 , Bdd[j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
      } } }
}

void openGlInterface::afficherListeTexte() {
  for (int i=0; i < tmpDico.size(); i++) {
    //    if (tmpDico.flagVisible==true) {
      //## Récupère les données de l'enregistrement ############################
      s_Allemand=tmpDico[i][0];
      s_Francais=tmpDico[i][1];
	
      glColor4f(0.2, 0.4, 0.4, 1.0);
		//tmpDico.color[R] , tmpDico.color[G] , tmpDico.color[B] , tmpDico.color[A] );

      //## Allemand ############################################################
      //      if (tmpDico.flagQuestionVisible) {
      glRasterPos2f(0.0 -glutGet(GLUT_WINDOW_WIDTH)/2 , -(i*20)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Allemand.c_str());
	//      }
      //## Francais ############################################################
	//      if (tmpDico.flagMemoVisible) {
	glRasterPos2f(200 -glutGet(GLUT_WINDOW_WIDTH)/2, -(i*20)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Francais.c_str());
	//      }

    }
  //}
    for (int i=0; i < tmpHauftig.size(); i++) {
    //    if (tmpHauftig.flagVisible==true) {
      //## Récupère les données de l'enregistrement ############################
      s_Allemand=tmpHauftig[i][0];
      s_Francais=tmpHauftig[i][1];
	
      glColor4f(0.4, 0.4, 0.2, 1.0);
		//tmpHauftig.color[R] , tmpHauftig.color[G] , tmpHauftig.color[B] , tmpHauftig.color[A] );

      //## Allemand ############################################################
      //      if (tmpHauftig.flagQuestionVisible) {
      glRasterPos2f(0.0 , -(i*20-10)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Allemand.c_str());
	//      }
      //## Francais ############################################################
	//      if (tmpHauftig.flagMemoVisible) {
	glRasterPos2f(200, -(i*20-10)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Francais.c_str());
	//      }

    }
  //}
        for (int i=0; i < tmpDicoXhauftig.size(); i++) {
    //    if (tmpDicoXhauftig.flagVisible==true) {
      //## Récupère les données de l'enregistrement ############################
      s_Allemand=tmpDicoXhauftig[i][0];
      s_Francais=tmpDicoXhauftig[i][1];
	
      glColor4f(0.8, 0.2, 0.2, 1.0);
		//tmpDicoXhauftig.color[R] , tmpDicoXhauftig.color[G] , tmpDicoXhauftig.color[B] , tmpDicoXhauftig.color[A] );

      //## Allemand ############################################################
      //      if (tmpDicoXhauftig.flagQuestionVisible) {
      glRasterPos2f(0.0-glutGet(GLUT_WINDOW_WIDTH)/4 , -(i*20+15)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Allemand.c_str());
	//      }
      //## Francais ############################################################
	//      if (tmpDicoXhauftig.flagMemoVisible) {
	glRasterPos2f(200-glutGet(GLUT_WINDOW_WIDTH)/4, -(i*20+15)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2);
	print_string(font_base, s_Francais.c_str());
	//      }

    }
  //}
    
  //## TABLES ################################################
  for (int j=0; j < Bdd.size(); j++) {
    for (int i=0; i < Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Récupère les données de l'enregistrement ############################
	s_Allemand=Bdd[j][i][0];
	s_Francais=Bdd[j][i][1];
	
	glColor4f(Bdd[j].color[R] , Bdd[j].color[G] , Bdd[j].color[B] , Bdd[j].color[A] );

	//## Allemand ############################################################
	if (Bdd[j].flagQuestionVisible) {
	  glRasterPos2f((Bdd[j].pos[X] + 10.0 -300 - pos[X])*ratio[X], (-(i*20+10) - pos[Y] - offsety)*ratio[Y]);
	  print_string(font_base, s_Allemand.c_str());
	}
	//## Francais ############################################################
	if (Bdd[j].flagMemoVisible) {
	  glRasterPos2f((Bdd[j].pos[X] + 10.0 + 300 - pos[X])*ratio[X], (-(i*20+10) - pos[Y] - offsety)*ratio[Y]);
	  print_string(font_base, s_Francais.c_str());
	}
	
      } } } }

void openGlInterface::afficherListe(){
  afficherListeDessin1 ();
  afficherListeDessin2 ();
  gestionListe_affichageMenuHorizontal();
  //  gestionListe_affichageMenuVertical(Bdd.size());
  afficherListeTexte   ();
}

void openGlInterface::interrogation(){
  /* Clear the window. */
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  afficherListe();
  if(!pause) {
    glutSwapBuffers();
    glutPostRedisplay();
  }
}

void openGlInterface::my_handle_key(unsigned char key, int x, int y) {
  tableBergson maTableVide2;
  switch (key) {
    cout << "clavier" << endl;
  case 'a': case 'A': gestionListe_gestionCurseur(-1); break;
  case 'z': case 'Z': gestionListe_gestionCurseur(+1); break;
    
  case 'v': case 'V': Bdd[posxCurseur].flagVisible         = !Bdd[posxCurseur].flagVisible; break;
  case 'c': case 'C': Bdd[posxCurseur].flagQuestionVisible = !Bdd[posxCurseur].flagQuestionVisible; break;
  case 'n': case 'N': Bdd.push_back(maTableVide2);
    break;
  case 'b': case 'B': Bdd[posxCurseur].flagMemoVisible     = !Bdd[posxCurseur].flagMemoVisible; break;
    
  case '-': offsety-=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;
  case '+': offsety+=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;

  case 27:              exit(1);           break;
  case 'p': case 'P':   pause = !pause;    break;
  case 's': case 'S':   saveMetaData();    break;
  case 'l': case 'L':   loadMetaData();    break;
  default:  break;
} }

//#############################################
//#############################################

int openGlInterface::loadMetaData() {
  ifstream in(fileName, std::ios::binary);
  in.unsetf(std::ios::skipws);
  int oldTailleBdd = Bdd.size();
  int tailleBdd;
  
  //## LECTURE DES MÉTADONNÉES GLOBALES #########
  RECORD   s_Lego;
  RECORD_F f_Lego;
  RECORD_I i_Lego;

  f_Lego.loadBinaire(&in);
  i_Lego.loadBinaire(&in);
  s_Lego.loadBinaire(&in);
  
  pos[X]            = f_Lego[0];
  pos[Y]            = f_Lego[1];
  ratio[X]          = f_Lego[2];
  ratio[Y]          = f_Lego[3];
  old[X]            = f_Lego[4];
  old[Y]            = f_Lego[5];
  offsety           = f_Lego[6];

  pause             = i_Lego[0];
  leftState         = i_Lego[1];
  rightState        = i_Lego[2];
  nearestTableIndex = i_Lego[3];
  posxCurseur       = i_Lego[4];
  tailleBdd         = i_Lego[5];

  fileName2         = s_Lego[0];
  cout << "fileName:" << fileName << endl;

  //## LECTURE DES TABLES ###########
  for (int i=0; i< oldTailleBdd; i++) 
    Bdd.erase(Bdd.begin());

  for (int i=0; i< tailleBdd; i++) {
    tableBergson maTableVide;
    maTableVide.loadBinaire(&in);
    Bdd.push_back(maTableVide);
  }
  
  //## LECTURE DES MÉTADONNÉES DES TABLES ######
  for (int i=0; i < Bdd.size(); i++) {
    RECORD_F f_Liste;
    RECORD_D d_Liste;
    RECORD_I i_Liste;
    RECORD s_Liste;
    
    f_Liste.loadBinaire(&in);
    d_Liste.loadBinaire(&in);
    i_Liste.loadBinaire(&in);
    s_Liste.loadBinaire(&in);
    
    Bdd[i].color[R]=		 f_Liste[0];
    Bdd[i].color[G]=	       	 f_Liste[1];
    Bdd[i].color[B]=	       	 f_Liste[2];
    Bdd[i].color[A]=             f_Liste[3];

    Bdd[i].pos[X]=		 d_Liste[0];

    Bdd[i].flagVisible=	         i_Liste[0];
    Bdd[i].flagQuestionVisible=  i_Liste[1];
    Bdd[i].flagMemoVisible=      i_Liste[2];

    Bdd[i].filename.assign(      s_Liste[0]);
  }
  
  in.close();
  return true;
}

//#############################################
//#############################################

int openGlInterface::saveMetaData() {
  ofstream out(fileName, std::ios::binary);
  out.unsetf(std::ios::skipws);

  //## SAUVEGARDE DES MÉTADONNÉES GLOBALES ####
  
  RECORD   s_Lego;
  RECORD_F f_Lego;
  RECORD_I i_Lego;
  
  f_Lego.push_back(pos[X]);
  f_Lego.push_back(pos[Y]);
  f_Lego.push_back(ratio[X]);
  f_Lego.push_back(ratio[Y]);
  f_Lego.push_back(old[X]);
  f_Lego.push_back(old[Y]);
  f_Lego.push_back(offsety);
  f_Lego.saveBinaire(&out);
  
  i_Lego.push_back(pause);
  i_Lego.push_back(leftState);
  i_Lego.push_back(rightState);
  i_Lego.push_back(nearestTableIndex);
  i_Lego.push_back(posxCurseur);
  i_Lego.push_back(Bdd.size());
  i_Lego.saveBinaire(&out);
  
  s_Lego.push_back(fileName);
  s_Lego.saveBinaire(&out);
  
  //## SAUVEGARDE DES TABLES #######
  //  out.setf(std::ios::skipws);
  for (int i=0; i< Bdd.size(); i++)
    Bdd[i].saveBinaire(&out);

  //## SAUVEGARDE DES MÉTADONNÉES DES TABLES ##
  for (int i=0; i < Bdd.size(); i++) {
    RECORD_F f_Liste;
    RECORD_D d_Liste;
    RECORD_I i_Liste;
    RECORD   s_Liste;
    
    f_Liste.push_back(Bdd[i].color[R]);
    f_Liste.push_back(Bdd[i].color[G]);	       
    f_Liste.push_back(Bdd[i].color[B]);	       
    f_Liste.push_back(Bdd[i].color[A]);            
    d_Liste.push_back(Bdd[i].pos[X]);
    i_Liste.push_back(Bdd[i].flagVisible);
    i_Liste.push_back(Bdd[i].flagQuestionVisible);
    i_Liste.push_back(Bdd[i].flagMemoVisible);
    s_Liste.push_back(Bdd[i].filename);
    
    f_Liste.saveBinaire(&out);
    d_Liste.saveBinaire(&out);
    i_Liste.saveBinaire(&out);
    s_Liste.saveBinaire(&out);
  }
  
  out.close();
  return true;
}

//#############################################

void openGlInterface::gestionListe_gestionCurseur(int Sens) {
  if ( Sens == -1 ) posxCurseur--; else posxCurseur++;
  if ( posxCurseur == -1 ) posxCurseur = Bdd.size() -1;
  if ( posxCurseur >= Bdd.size() ) posxCurseur=0;
}


void openGlInterface::gestionListe_affichageMenuHorizontal(){
  double x_debut,x_fin, x_delta, y_debut, y_fin, y_delta;
  double x_tailleFenetre, y_tailleFenetre;

  x_delta=glutGet(GLUT_WINDOW_WIDTH)-10;    x_debut=-(x_delta/2);      x_fin=x_delta/2;    
  y_delta=glutGet(GLUT_WINDOW_HEIGHT)-10;   y_debut=(y_delta/2);      y_fin=(y_delta/2)-30;    

  x_tailleFenetre = (x_delta / Bdd.size());
  y_tailleFenetre = y_debut-y_fin;

  for (int i=0; i < Bdd.size(); i++) {
    if (posxCurseur==i)
      glColor4f(Bdd[i].color[0]/1.5, Bdd[i].color[1]/1.5, Bdd[i].color[2]/1.5, Bdd[i].color[3]);
    else
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);

    gestionListe_rectanglePlein(x_debut+x_tailleFenetre*i, y_debut, x_debut+x_tailleFenetre*(i+1), y_fin);

    glColor4f(Bdd[i].color[0], Bdd[i].color[1], Bdd[i].color[2], Bdd[i].color[3]);
    glRasterPos2f( x_debut+x_tailleFenetre*i+10, (y_debut + y_fin)/2 );
    print_string( font_base, Bdd[i].filename.c_str() );
  }

  for (int i=0; i < Bdd.size(); i++) {
    if (posxCurseur==i) {
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);
      gestionListe_rectangle(x_debut+x_tailleFenetre*i, y_debut, x_debut+x_tailleFenetre*(i+1), y_fin);
    }
  }
}

void openGlInterface::gestionListe_affichageMenuVertical(){
  double x_debut,x_fin, x_delta, y_debut, y_fin, y_delta;
  double x_tailleFenetre, y_tailleFenetre;

  x_delta=glutGet(GLUT_WINDOW_WIDTH)-10;   x_debut=-(x_delta/2);      x_fin=-(x_delta/2)+30;    
  y_delta=glutGet(GLUT_WINDOW_HEIGHT)-10;    y_debut=(y_delta/2);      y_fin=-y_delta/2;
  
  x_tailleFenetre = x_debut-x_fin;
  y_tailleFenetre = (y_delta / Bdd.size());

  for (int i=0; i < Bdd.size(); i++) {
    if (posxCurseur==i)
      glColor4f(Bdd[i].color[0]/1.5, Bdd[i].color[1]/1.5, Bdd[i].color[2]/1.5, Bdd[i].color[3]);
    else
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);

    gestionListe_rectanglePlein(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));

    glColor4f(Bdd[i].color[0], Bdd[i].color[1], Bdd[i].color[2], Bdd[i].color[3]);
    glRasterPos2f( x_debut+10, y_debut-(y_tailleFenetre*(i+0.5)) );
    print_string(font_base, Bdd[i].filename.c_str() );
  }

  for (int i=0; i < Bdd.size(); i++) {
    if (posxCurseur==i) {
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);
      gestionListe_rectangle(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));
    }
  }
}

