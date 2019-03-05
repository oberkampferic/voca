#include "openGl.hpp"
//#include "openGlWindows.cpp"

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

  
  vector<tableBergson > maBddVide;
  tableBergson maTableVide;

  //pour la sauvegarde binaire
  fileName = argv[1];
  
  //## fichier isolé #######################################
  if (extension.compare(".txt")==0){
    ServerBdd.push_back(maBddVide);
    ServerBdd.back().push_back(maTableVide);
    ServerBdd.back().back().importDriver(nomFichier);
    ServerBdd.back()[0].filename.assign(nomFichier);
    ServerBdd.back()[0].color[R]            = 0.0; 
    ServerBdd.back()[0].color[G]	    = 1.0; 
    ServerBdd.back()[0].color[B]	    = 1.0; 
    ServerBdd.back()[0].color[A]            = 1.0; 
    ServerBdd.back()[0].pos[X]	            = 0.0; 
    ServerBdd.back()[0].flagVisible         = 1;   
    ServerBdd.back()[0].flagQuestionVisible = 1;   
    ServerBdd.back()[0].flagMemoVisible     = 1;   

//  ofstream tmpOut("cronimousHumain.txt");
//  ServerBdd.back()[0].saveHumain(&tmpOut);
//  tmpOut.close();
  }
  //## liste de fichiers ###################################
  else   if (extension.compare(".lst")==0){
    fileNameListe.assign(nomFichier);
    maListeDeListe.importDriver(nomFichier);
    ServerBdd.push_back(maBddVide);
    for (int i=0; i < maListeDeListe.size(); i++) {
      cout << "On charge: " << maListeDeListe[i][0] << endl;
      ServerBdd.back().push_back(maTableVide);
      ServerBdd.back().back().importDriver(maListeDeListe[i][0]);
      ServerBdd.back()[i].filename.assign(maListeDeListe[i][0]);
      ServerBdd.back()[i].color[R]            = stof(maListeDeListe[i][1]);
      ServerBdd.back()[i].color[G]	           = stof(maListeDeListe[i][2]);
      ServerBdd.back()[i].color[B]	           = stof(maListeDeListe[i][3]);
      ServerBdd.back()[i].color[A]            = stof(maListeDeListe[i][4]);
      ServerBdd.back()[i].pos[X]	           = stod(maListeDeListe[i][5]);
      ServerBdd.back()[i].flagVisible         = stoi(maListeDeListe[i][6]);
      ServerBdd.back()[i].flagQuestionVisible = stoi(maListeDeListe[i][7]);
      ServerBdd.back()[i].flagMemoVisible     = stoi(maListeDeListe[i][8]);
      cout << "Table chargée." << endl;

    }
  }
  //## liste de fichiers ###################################
  else   if (extension.compare(".ls2")==0){
    fileNameListe.assign(nomFichier);
    maListeDeListe.importDriver(nomFichier);
    for (int i=0; i < maListeDeListe.size(); i++) {
      cout << "On charge: " << maListeDeListe[i][0] << " ... " << endl;
      ServerBdd.push_back(maBddVide);
      ServerBdd.back().push_back(maTableVide);
      ServerBdd.back().back().importDriver(maListeDeListe[i][0]);
      ServerBdd.back().back().filename.assign(maListeDeListe[i][0]);
      ServerBdd.back().back().color[R]            = 0.0; 
      ServerBdd.back().back().color[G]	           = 1.0; 
      ServerBdd.back().back().color[B]	           = 1.0; 
      ServerBdd.back().back().color[A]            = 1.0; 
      ServerBdd.back().back().pos[X]	           = 0.0; 
      ServerBdd.back().back().flagVisible         = 1;   
      ServerBdd.back().back().flagQuestionVisible = 1;   
      ServerBdd.back().back().flagMemoVisible     = 1;
      cout << "Chargé." << endl;
    }
  }
  //## fichier binaire #####################################
  else   if (extension.compare(".bin")==0){
    loadMetaData();
  }
  //pour la sauvegarde binaire.
  // Attention, loadMetaData se sert de ce nom.
  fileName = fileName + ".save";

  //  monDico.importDriver          ("listes/dico.txt");
  monDico.importDriver          ("listes/cronimousHumain3.txt");
  monHauftisteWorte.importDriver("listes/haufigstenWorte.txt");
  monHauftisteWorte.importDriver("listes/dico.txt");
  prefixe.importDriver          ("listes/prefixe.txt");
  suffixe.importDriver          ("listes/suffixes.txt");
  
  //########################################################
  //## INITIALISATION OPENGL SDL ###########################

  SDL_Init(SDL_INIT_VIDEO);
  last_time = SDL_GetTicks();
  
  glutInit(&argc, argv);
  glutInitWindowSize(800, 700);

  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

  strcpy(window_title, "glxfont: ");
  strcpy(font_name, "fixed");
  strcat(window_title, font_name);
  glutCreateWindow(window_title);

  my_init(font_name);

  glutReshapeFunc(my_reshape);
  glutMotionFunc(my_motionMouse);
  glutPassiveMotionFunc(my_motionMousePassive);
  glutMouseFunc(my_mouse);
  glutKeyboardFunc(my_handle_key);
}

void openGlInterface::init_font(GLuint base, char * f, int idFont) {
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
    cout << "Changement de font. font n°" << idFont << endl;
    switch(idFont) {
    /* Load the font. */
#include "listeFont.cpp"
    default: return;
    }

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
  else  init_font(font_base, "fixed", 1);
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
  activerAffichage=true;
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
      ServerBdd[posyCurseur][nearestTableIndex].pos[X]-=delta[X]/ratio[X];
      old[X]=x;
    }
    //  }
    activerAffichage=true; 
}

void openGlInterface::my_motionMousePassive(int x, int y) {
  float delta[2];
  colonneConcernee(x, y);
  einfugemarkewort=motConcerne(x,y);	//Identifier quel est le mot le plus proche.
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
      ServerBdd[posyCurseur][nearestTableIndex].pos[X]-=delta[X]/ratio[X];
      old[X]=x;
    }
    //  }
    activerAffichage=true; 
}


double carreFunc(double x1) {
  return x1*x1;
}

void openGlInterface::colonneConcernee(int x, int y) {
  double monDeltaX, bestDeltaX;
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;

  nearestTableIndex = 0;
  posxCurseur= 0;

  if (ServerBdd[posyCurseur].size()>0) { //besoin d'initialiser
    bestDeltaX = carreFunc(ServerBdd[posyCurseur][0].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
    posxCurseur= 0;
    nearestTableIndex = 0;
  }
  if (ServerBdd[posyCurseur].size()>1) { 
    for (int i=1; i< ServerBdd[posyCurseur].size(); i++) { 
      monDeltaX = carreFunc(ServerBdd[posyCurseur][i].pos[X] - ((((double) x - widthSur2 ) / ratio[X]) + pos[X]));
      if (monDeltaX<bestDeltaX) {
	bestDeltaX=monDeltaX;
	posxCurseur= i;
	nearestTableIndex = i;
      }
    }
  }
}

int openGlInterface::motConcerne(int x, int y) {
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;
  double projY= (((double) y - (double) heightSur2 ) / ratio[Y])- pos[Y];
  projY/=20; 
  if ((projY<ServerBdd[posyCurseur][nearestTableIndex].size()) && (projY>=0))
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
      cout << ServerBdd[posyCurseur][nearestTableIndex][(int) projY][0] << " <=> "
	   << ServerBdd[posyCurseur][nearestTableIndex][(int) projY][1] << "##################" << endl;

      //### PARTIE RECHERCHE DU RADICAL ############################################
      radical(ServerBdd[posyCurseur][nearestTableIndex][(int) projY][0], s_radical);
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
	  if (ServerBdd[posyCurseur].size()>1) { //une seule table?
	    if (nearestTableIndex == 0)       prochaineTableIndex=  (ServerBdd[posyCurseur].size()-1);
	    else                   	    prochaineTableIndex = nearestTableIndex-1;
	    ServerBdd[posyCurseur][prochaineTableIndex].push_back( ServerBdd[posyCurseur][nearestTableIndex][(int) projY] );
	    ServerBdd[posyCurseur][nearestTableIndex].erase(ServerBdd[posyCurseur][nearestTableIndex].begin()+(int) projY);
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
	    if (ServerBdd[posyCurseur].size()>1) { //une seule table?
	      if ((nearestTableIndex) < (ServerBdd[posyCurseur].size()-1)) prochaineTableIndex = nearestTableIndex+1;
	      else                            	    prochaineTableIndex = 0;
	      ServerBdd[posyCurseur][prochaineTableIndex].push_back( ServerBdd[posyCurseur][nearestTableIndex][(int) projY] );
	      ServerBdd[posyCurseur][nearestTableIndex].erase(ServerBdd[posyCurseur][nearestTableIndex].begin()+(int) projY);
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
  activerAffichage=true; 
}
  
void openGlInterface::afficherListeDessin1(){
  double ratioCoul=1;
  for (int j=0; j <ServerBdd[posyCurseur].size(); j++) {
    for (int i=0; i< ServerBdd[posyCurseur][j].size(); i++) {
      if (ServerBdd[posyCurseur][j].flagVisible==true) {
	//## Carré vertical #################################################
	if (j==posxCurseur)
	  if (ratioCoul < 0.6) ratioCoul=0.8; else ratioCoul=0.3;
	else
	  if (ratioCoul < 0.6) ratioCoul=0.7; else ratioCoul=0.4;
	
	glColor4f( (ServerBdd[posyCurseur][j].color[R] * ratioCoul) / 3,
		   (ServerBdd[posyCurseur][j].color[G] * ratioCoul) / 3,
		   (ServerBdd[posyCurseur][j].color[B] * ratioCoul) / 3,
		   ServerBdd[posyCurseur][j].color[A] * 0.2 );
		
	glColor4f( (ServerBdd[posyCurseur][j].color[R] * ratioCoul) / 3,
		   (ServerBdd[posyCurseur][j].color[G] * ratioCoul) / 3,
		   (ServerBdd[posyCurseur][j].color[B] * ratioCoul) / 3,
		   ServerBdd[posyCurseur][j].color[A] * 0.2 );
		  farbeTabelle meinFarbenTabelle3(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 1.0);
	  glColor4f(meinFarbenTabelle3[j][0],meinFarbenTabelle3[j][1],meinFarbenTabelle3[j][2],meinFarbenTabelle3[j][3]);
	glBegin(GL_QUADS);{
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] + 010 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] + 600 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );      
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] + 600 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] + 010 - pos[X] )*ratio[X] ,( -(i*20) - pos[Y])*ratio[Y] );
	}    glEnd();
	//## CarréDate ###########################################################
	glColor4f(ServerBdd[posyCurseur][j].color[R] * ratioCoul  , ServerBdd[posyCurseur][j].color[G] * ratioCoul , ServerBdd[posyCurseur][j].color[B] * ratioCoul , ServerBdd[posyCurseur][j].color[A] *0.5);
	glBegin(GL_QUADS);{
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] - 10 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] - 80 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);      
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] - 80 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f( (ServerBdd[posyCurseur][j].pos[X] - 10 - pos[X] )*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
	
      } } }
}

void openGlInterface::afficherListeDessin2(){
  double ratioCoul=1;

  for (int j=0; j <ServerBdd[posyCurseur].size(); j++) {
    for (int i=0; i< ServerBdd[posyCurseur][j].size(); i++) {
      if (ServerBdd[posyCurseur][j].flagVisible==true) {
	//## Ligne horizontale Date 1#############################################
	glColor4f(ServerBdd[posyCurseur][j].color[R] * 0.5, ServerBdd[posyCurseur][j].color[G] *0.5, ServerBdd[posyCurseur][j].color[B] *0.5, ServerBdd[posyCurseur][j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
	//## Ligne horizontale Date 2#############################################
	glColor4f(ServerBdd[posyCurseur][j].color[R]* 0.2 , ServerBdd[posyCurseur][j].color[G]* 0.2 , ServerBdd[posyCurseur][j].color[B]* 0.2 , ServerBdd[posyCurseur][j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[X],( -(i*20) - pos[Y])*ratio[Y]);
	}    glEnd();
      } } }
}

void openGlInterface::afficherListeTexte() {
  //############################################################################
  //## DICTIONNAIRE ############################################################
  //############################################################################
  for (int i=0; i < tmpDico.size(); i++) {
    //    if (tmpDico.flagVisible==true) {
    //## Récupère les données de l'enregistrement ############################
    s_Allemand=tmpDico[i][0];
    s_Francais=tmpDico[i][1];
	
    glColor4f(0.2, 0.4, 0.4, 1.0);
    //tmpDico.color[R] , tmpDico.color[G] , tmpDico.color[B] , tmpDico.color[A] );

    //## Allemand ############################################################
    //      if (tmpDico.flagQuestionVisible) {
    print_string (0.0 -glutGet(GLUT_WINDOW_WIDTH)/2 , -(i*20)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2,
		  font_base, &s_Allemand);
    //      }
    //## Francais ############################################################
    //      if (tmpDico.flagMemoVisible) {
    print_string (200 -glutGet(GLUT_WINDOW_WIDTH)/2, -(i*20)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2, 
		  font_base, &s_Francais);
    //      }

  }
  //}
  //############################################################################
  //## HAUTFIG #################################################################
  //############################################################################
  for (int i=0; i < tmpHauftig.size(); i++) {
    //    if (tmpHauftig.flagVisible==true) {
    //## Récupère les données de l'enregistrement ############################
    s_Allemand=tmpHauftig[i][0];
    s_Francais=tmpHauftig[i][1];
	
    glColor4f(0.4, 0.4, 0.2, 1.0);
    //tmpHauftig.color[R] , tmpHauftig.color[G] , tmpHauftig.color[B] , tmpHauftig.color[A] );

    //## Allemand ############################################################
    //      if (tmpHauftig.flagQuestionVisible) {
    print_string (0.0 , -(i*20-10)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2,
		  font_base, &s_Allemand);
    //      }
    //## Francais ############################################################
    //      if (tmpHauftig.flagMemoVisible) {
    print_string (200, -(i*20-10)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2, 
		  font_base, &s_Francais);
    //      }

  }
  //}
  //############################################################################
  //## CROISEMENT HAUFTIG DICO #################################################
  //############################################################################
  for (int i=0; i < tmpDicoXhauftig.size(); i++) {
    //    if (tmpDicoXhauftig.flagVisible==true) {
    //## Récupère les données de l'enregistrement ############################
    s_Allemand=tmpDicoXhauftig[i][0];
    s_Francais=tmpDicoXhauftig[i][1];
	
    glColor4f(0.8, 0.2, 0.2, 1.0);
    //tmpDicoXhauftig.color[R] , tmpDicoXhauftig.color[G] , tmpDicoXhauftig.color[B] , tmpDicoXhauftig.color[A] );

    //## Allemand ############################################################
    //      if (tmpDicoXhauftig.flagQuestionVisible) {
    print_string (0.0-glutGet(GLUT_WINDOW_WIDTH)/4 , -(i*20+15)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2, 
		  font_base, &s_Allemand);
    //      }
    //## Francais ############################################################
    //      if (tmpDicoXhauftig.flagMemoVisible) {
    print_string (200-glutGet(GLUT_WINDOW_WIDTH)/4, -(i*20+15)-60 +glutGet(GLUT_WINDOW_HEIGHT)/2,
		  font_base, &s_Francais);
    //      }
  }
  //}
  //############################################################################
  //## TABLES ##################################################################
  //############################################################################

  for (int j=0; j < ServerBdd[posyCurseur].size(); j++) {
    for (int i=0; i < ServerBdd[posyCurseur][j].size(); i++) {
      farbeTabelle meinFarbenTabelle(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 0.8);
      glColor4f(meinFarbenTabelle[j][0],meinFarbenTabelle[j][1],meinFarbenTabelle[j][2],meinFarbenTabelle[j][3]);

      if (j==posxCurseur) {
	farbeTabelle meinFarbenTabelle2(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 0.9);
	glColor4f(meinFarbenTabelle2[j][0],meinFarbenTabelle2[j][1],meinFarbenTabelle2[j][2],meinFarbenTabelle2[j][3]);
      }


      if (ServerBdd[posyCurseur][j].flagVisible==true) {
	//## Récupère les données de l'enregistrement ############################
	s_Allemand=ServerBdd[posyCurseur][j][i][0];
	s_Francais=ServerBdd[posyCurseur][j][i][1];


	//	if ((i==einfugemarkewort) && (j==posxCurseur)){
	  if (i==einfugemarkewort) {
	  farbeTabelle meinFarbenTabelle3(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 1.0);
	  glColor4f(meinFarbenTabelle3[j][0],meinFarbenTabelle3[j][1],meinFarbenTabelle3[j][2],meinFarbenTabelle3[j][3]);
	}

	//## Allemand ############################################################
	if (ServerBdd[posyCurseur][j].flagQuestionVisible) {
	  print_string ((ServerBdd[posyCurseur][j].pos[X] + 10.0 -300 - pos[X])*ratio[X], (-(i*20+10) - pos[Y] - offsety)*ratio[Y], 
			font_base, &s_Allemand);
	}
	//## Francais ############################################################
	if (ServerBdd[posyCurseur][j].flagMemoVisible) {
	  print_string ((ServerBdd[posyCurseur][j].pos[X] + 10.0 + 300 - pos[X])*ratio[X], (-(i*20+10) - pos[Y] - offsety)*ratio[Y], 
			font_base, &s_Francais);
	}
	
      } } } }

void openGlInterface::afficherListe(){
  afficherListeDessin1 ();
  afficherListeDessin2 ();

  gestionListe_affichageMenuHorizontal();
  gestionListe_affichageMenuVertical(); 
  afficherListeTexte   ();
}

void openGlInterface::interrogation(){
  start_time = SDL_GetTicks(); 

  current_time = SDL_GetTicks();
  ellapsed_time = current_time - last_time;
  last_time = current_time;

    /* Clear the window. */
  if (activerAffichage==true) {
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT); 

    glLoadIdentity();

    afficherListe();

    glFlush();
    glutSwapBuffers();

    activerAffichage=false;
  }
    glutPostRedisplay();
    
  ellapsed_time = SDL_GetTicks() - start_time;
  if (ellapsed_time < 20) {
    int delay = 20 - ellapsed_time;
    // cout << "Temps:" << ellapsed_time << " : " << delay << endl;
    SDL_Delay(delay);
  }

}

void openGlInterface::my_handle_key(unsigned char key, int x, int y) {
  tableBergson maTableVide2;

  #include "keyboard.cpp"

  activerAffichage=true; 
}

//#############################################
//#############################################

int openGlInterface::loadMetaData() {
  ifstream in(ServerBdd[posyCurseur][0].filename + ".save" , std::ios::binary);
  cout << "loadMetaData: nomFichier: " << ServerBdd[posyCurseur][0].filename + ".save" << endl;
  if (in.is_open()) {
    in.unsetf(std::ios::skipws);
    int oldTailleServerBdd = ServerBdd[posyCurseur].size();
    int tailleServerBdd;
  
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
    tailleServerBdd         = i_Lego[5];
    fileName2         = s_Lego[0];
    cout << "fileName:" << fileName << endl;

    //## LECTURE DES TABLES ###########
    for (int i=0; i< oldTailleServerBdd; i++) 
      ServerBdd[posyCurseur].erase(ServerBdd[posyCurseur].begin());
    for (int i=0; i< tailleServerBdd; i++) {
      tableBergson maTableVide;
      maTableVide.loadBinaire(&in);
      ServerBdd[posyCurseur].push_back(maTableVide);
    }
    //## LECTURE DES MÉTADONNÉES DES TABLES ######
    for (int i=0; i < ServerBdd[posyCurseur].size(); i++) {
      RECORD_F f_Liste;
      RECORD_D d_Liste;
      RECORD_I i_Liste;
      RECORD s_Liste;
    
      f_Liste.loadBinaire(&in);
      d_Liste.loadBinaire(&in);
      i_Liste.loadBinaire(&in);
      s_Liste.loadBinaire(&in);
    
      ServerBdd[posyCurseur][i].color[R]=		 f_Liste[0];
      ServerBdd[posyCurseur][i].color[G]=	       	 f_Liste[1];
      ServerBdd[posyCurseur][i].color[B]=	       	 f_Liste[2];
      ServerBdd[posyCurseur][i].color[A]=             f_Liste[3];

      ServerBdd[posyCurseur][i].pos[X]=		 d_Liste[0];

      ServerBdd[posyCurseur][i].flagVisible=	         i_Liste[0];
      ServerBdd[posyCurseur][i].flagQuestionVisible=  i_Liste[1];
      ServerBdd[posyCurseur][i].flagMemoVisible=      i_Liste[2];

      ServerBdd[posyCurseur][i].filename.assign(      s_Liste[0]);
    }
  
    in.close();
    return true;
  }
  return false;
}

//#############################################
//#############################################

int openGlInterface::saveMetaData() {
  ofstream out(ServerBdd[posyCurseur][0].filename + ".save", std::ios::binary);
  if (out.is_open()) {
    cout << "saveMetaData: nomFichier: " << ServerBdd[posyCurseur][0].filename + ".save" << endl;
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
    i_Lego.push_back(ServerBdd[posyCurseur].size());
    i_Lego.saveBinaire(&out);
  
    s_Lego.push_back(fileName);
    s_Lego.saveBinaire(&out);
  
    //## SAUVEGARDE DES TABLES #######
    //  out.setf(std::ios::skipws);
    for (int i=0; i< ServerBdd[posyCurseur].size(); i++)
      ServerBdd[posyCurseur][i].saveBinaire(&out);

    //## SAUVEGARDE DES MÉTADONNÉES DES TABLES ##
    for (int i=0; i < ServerBdd[posyCurseur].size(); i++) {
      RECORD_F f_Liste;
      RECORD_D d_Liste;
      RECORD_I i_Liste;
      RECORD   s_Liste;
    
      f_Liste.push_back(ServerBdd[posyCurseur][i].color[R]);
      f_Liste.push_back(ServerBdd[posyCurseur][i].color[G]);	       
      f_Liste.push_back(ServerBdd[posyCurseur][i].color[B]);	       
      f_Liste.push_back(ServerBdd[posyCurseur][i].color[A]);            
      d_Liste.push_back(ServerBdd[posyCurseur][i].pos[X]);
      i_Liste.push_back(ServerBdd[posyCurseur][i].flagVisible);
      i_Liste.push_back(ServerBdd[posyCurseur][i].flagQuestionVisible);
      i_Liste.push_back(ServerBdd[posyCurseur][i].flagMemoVisible);
      s_Liste.push_back(ServerBdd[posyCurseur][i].filename);
    
      f_Liste.saveBinaire(&out);
      d_Liste.saveBinaire(&out);
      i_Liste.saveBinaire(&out);
      s_Liste.saveBinaire(&out);
    }
  
    out.close();
    return true;
  }
  return false;
}

//#############################################

void openGlInterface::gestionListe_gestionCurseurX(int Sens) {
  if ( Sens == -1 ) posxCurseur--; else posxCurseur++;
  if ( posxCurseur == -1 ) posxCurseur = ServerBdd[posyCurseur].size() -1;
  if ( posxCurseur >= ServerBdd[posyCurseur].size() ) posxCurseur=0;
}

void openGlInterface::gestionListe_gestionCurseurY(int Sens) {
  if ( Sens == -1 ) posyCurseur--; else posyCurseur++;
  if ( posyCurseur == -1 ) posyCurseur = ServerBdd.size() -1;
  if ( posyCurseur >= ServerBdd.size() ) posyCurseur=0;
}


void openGlInterface::gestionListe_affichageMenuHorizontal(){
  double x_debut,x_fin, x_delta, y_debut, y_fin, y_delta;
  double x_tailleFenetre, y_tailleFenetre;

  x_delta=glutGet(GLUT_WINDOW_WIDTH)-10;    x_debut=-(x_delta/2);      x_fin=x_delta/2;    
  y_delta=glutGet(GLUT_WINDOW_HEIGHT)-10;   y_debut=(y_delta/2);      y_fin=(y_delta/2)-30;    

  x_tailleFenetre = (x_delta / ServerBdd[posyCurseur].size());
  y_tailleFenetre = y_debut-y_fin;

  for (int i=0; i < ServerBdd[posyCurseur].size(); i++) {
    if (posxCurseur==i) {
      farbeTabelle meinFarbenTabelle(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 0.5);
      glColor4f(meinFarbenTabelle[i][0],meinFarbenTabelle[i][1],meinFarbenTabelle[i][2],meinFarbenTabelle[i][3]);
      gestionListe_rectangle(x_debut+x_tailleFenetre*i, y_debut, x_debut+x_tailleFenetre*(i+1), y_fin);
      farbeTabelle meinFarbenTabelle2(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 0.66);
      glColor4f(meinFarbenTabelle2[i][0],meinFarbenTabelle2[i][1],meinFarbenTabelle2[i][2],meinFarbenTabelle2[i][3]);
    } else {
      farbeTabelle meinFarbenTabelle(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 0.5);
      glColor4f(meinFarbenTabelle[i][0],meinFarbenTabelle[i][1],meinFarbenTabelle[i][2],meinFarbenTabelle[i][3]);
    }

    gestionListe_rectanglePlein(x_debut+x_tailleFenetre*i, y_debut, x_debut+x_tailleFenetre*(i+1), y_fin);

    farbeTabelle meinFarbenTabelle(ServerBdd[posyCurseur].size(), einfugemarkefarbe+1, 1.0);
    glColor4f(meinFarbenTabelle[i][0],meinFarbenTabelle[i][1],meinFarbenTabelle[i][2],meinFarbenTabelle[i][3]);
    print_string ( x_debut+x_tailleFenetre*i+10, (y_debut + y_fin)/2, 
		   font_base, &ServerBdd[posyCurseur][i].filename );
  }
}

void openGlInterface::gestionListe_affichageMenuVertical(){
  double x_debut,x_fin, x_delta, y_debut, y_fin, y_delta;
  double x_tailleFenetre, y_tailleFenetre;

  

  x_delta=glutGet(GLUT_WINDOW_WIDTH)-10;   x_debut=-(x_delta/2);      x_fin=-(x_delta/2)+30;    
  y_delta=glutGet(GLUT_WINDOW_HEIGHT)-10;    y_debut=(y_delta/2);      y_fin=-y_delta/2;
  
  x_tailleFenetre = x_debut-x_fin;
  y_tailleFenetre = (y_delta / ServerBdd.size());
  
  for (int i=0; i < ServerBdd.size(); i++) {
    if (posyCurseur==i) {
      farbeTabelle meinFarbenTabelle(ServerBdd.size(), einfugemarkefarbe, 1.0);
      glColor4f(meinFarbenTabelle[i][0],meinFarbenTabelle[i][1],meinFarbenTabelle[i][2],meinFarbenTabelle[i][3]);
      gestionListe_rectangle(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));
    }
    else{
      farbeTabelle meinFarbenTabelle(ServerBdd.size(), einfugemarkefarbe, 0.5);
      glColor4f(meinFarbenTabelle[i][0],meinFarbenTabelle[i][1],meinFarbenTabelle[i][2],meinFarbenTabelle[i][3]);
    }
    gestionListe_rectanglePlein(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));
    print_string ( x_debut+10, y_debut-(y_tailleFenetre*(i+0.5)), 
    		   font_base, &ServerBdd[i][0].filename );
  }
}


// Poubelle

//
//  string test;
//  string test2;
//  int i;
//
//  for ( i=32; i<256; i++){
//    test2 = i;
//    test = test + " " + to_string (i) + " " + test2;
//
//    if ((i%32)==0) {
//      glRasterPos2f ( (float)(-glutGet(GLUT_WINDOW_WIDTH)/2), -(float) i);
//      print_string(font_base, &test);
//      test = "";
//    }
//  };
//  glRasterPos2f ( (float)(-glutGet(GLUT_WINDOW_WIDTH)/2), -(float) (i+32));
//  unsigned char c;
//  test="";
//  c = 'ü'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'ö'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'ä'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'Ä'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'Ö'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'Ü'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'é'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'è'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'ê'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'à'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'ç'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  c = 'ß'; test2 = c; test = test + to_string(c) + " " + test2 + "\t";
//  print_string(font_base, &test);
//  test="";
//  c = 220; test += c;
//  c = 196; test += c;
//
//  parser MonParser;
//  string testModel = "Ich bin verfügbar.";
//  c=220; test=c; MonParser.ReplaceString (&testModel, "Ü", test);
//  c=220; test=c; MonParser.ReplaceString (&testModel, "ü", test);
//  c=214; test=c; MonParser.ReplaceString (&testModel, "Ö", test);
//  c=214; test=c; MonParser.ReplaceString (&testModel, "ö", test);
//  c=196; test=c; MonParser.ReplaceString (&testModel, "Ä", test);
//  c=196; test=c; MonParser.ReplaceString (&testModel, "ä", test);
//  c=223; test=c; MonParser.ReplaceString (&testModel, "ß", test);
//  
//  c=201; test=c; MonParser.ReplaceString (&testModel, "é", test);
//  c=200; test=c; MonParser.ReplaceString (&testModel, "è", test);
//  c=202; test=c; MonParser.ReplaceString (&testModel, "ê", test);
//  c=224; test=c; MonParser.ReplaceString (&testModel, "à", test);
//  c=199; test=c; MonParser.ReplaceString (&testModel, "ç", test);
//
//  print_string(font_base, &testModel);
