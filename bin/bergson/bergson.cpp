#include "bergson.hpp"

void bergson::afficherListeDessin1(){
  double ratioCoul=0.1;
  for (int j=0; j <maListeDeListe.size(); j++) {
    for (int i=0; i< Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Récupère les données de l'enregistrement ########################
	s_Name  = Bdd[j][i][1];
	s_Date1 = Bdd[j][i][2];
	s_Date2 = Bdd[j][i][3];
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
	  glVertex2f( (Bdd[j].pos[X] + 010 - pos[X] )*ratio[0] ,(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y] );
	  glVertex2f( (Bdd[j].pos[X] + 600 - pos[X] )*ratio[0] ,(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y] );      
	  glVertex2f( (Bdd[j].pos[X] + 600 - pos[X] )*ratio[0] ,(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y] );
	  glVertex2f( (Bdd[j].pos[X] + 010 - pos[X] )*ratio[0] ,(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y] );
	}    glEnd();
	//## CarréDate ###########################################################
	glColor4f(Bdd[j].color[R] * ratioCoul  , Bdd[j].color[G] * ratioCoul , Bdd[j].color[B] * ratioCoul , Bdd[j].color[A] *0.5);
	glBegin(GL_QUADS);{
	  glVertex2f( (Bdd[j].pos[X] - 10 - pos[X] )*ratio[0],(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y]);
	  glVertex2f( (Bdd[j].pos[X] - 80 - pos[X] )*ratio[0],(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y]);      
	  glVertex2f( (Bdd[j].pos[X] - 80 - pos[X] )*ratio[0],(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y]);
	  glVertex2f( (Bdd[j].pos[X] - 10 - pos[X] )*ratio[0],(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y]);
	}    glEnd();
	
      } } } }

void bergson::afficherListeDessin2(){
  for (int j=0; j <maListeDeListe.size(); j++) {
    for (int i=0; i< Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Récupère les données de l'enregistrement ############################
	s_Name = Bdd[j][i][1];
	s_Date1 = Bdd[j][i][2];
	s_Date2 = Bdd[j][i][3];
	//## Ligne horizontale Date 1#############################################
	glColor4f(Bdd[j].color[R] * 0.5, Bdd[j].color[G] *0.5, Bdd[j].color[B] *0.5, Bdd[j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[0],(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[0] ,(1000.0 - stof(s_Date1) - pos[Y])*ratio[Y]);
	}    glEnd();
	//## Ligne horizontale Date 2#############################################
	glColor4f(Bdd[j].color[R]* 0.2 , Bdd[j].color[G]* 0.2 , Bdd[j].color[B]* 0.2 , Bdd[j].color[A] );
	glBegin(GL_LINES);{
	  glVertex2f((-2000 - pos[X])*ratio[0],(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y]);
	  glVertex2f(( 2000 - pos[X])*ratio[0] ,(1000.0 - stof(s_Date2) - pos[Y])*ratio[Y]);
	}    glEnd();
      } } } }

void bergson::afficherListeTexte() {
  for (int j=0; j < maListeDeListe.size(); j++) {
    for (int i=0; i < Bdd[j].size(); i++) {
      if (Bdd[j].flagVisible==true) {
	//## Récupère les données de l'enregistrement ############################
	s_Categorie = Bdd[j][i][0];
	s_Name      = Bdd[j][i][1];
	s_Date1     = Bdd[j][i][2];
	s_Date2     = Bdd[j][i][3];
	s_Memo      = Bdd[j][i][4];
		      
	glColor4f(Bdd[j].color[R] , Bdd[j].color[G] , Bdd[j].color[B] , Bdd[j].color[A] );
	//## Catégorie ###########################################################
	if (Bdd[j].flagQuestionVisible) {
	  glRasterPos2f((Bdd[j].pos[X] + 10.0 - 100 - pos[X])*ratio[0], (1000.0 - (stof(s_Date1) + stof(s_Date2)) /2 - pos[Y] - offsety)*ratio[Y]);
	  print_string(font_base, s_Categorie.c_str());
	}
	//## Nom  ################################################################
	glRasterPos2f((Bdd[j].pos[X] + 10.0 + 170 - pos[X])*ratio[0], (1000.0 - (stof(s_Date1) + stof(s_Date2)) /2 - pos[Y] - offsety)*ratio[Y]);
	print_string(font_base, s_Name.c_str());
	//## Date 1 ##############################################################
	glRasterPos2f((Bdd[j].pos[X] + 10.0 + 050 - pos[X])*ratio[0], (1000.0 - stof(s_Date1)                       - pos[Y] - offsety)*ratio[Y]);
	print_string(font_base, s_Date1.c_str());
	//## Date 2 ##############################################################
	glRasterPos2f((Bdd[j].pos[X] + 10.0 + 100 - pos[X])*ratio[0], (1000.0 - stof(s_Date2)                       - pos[Y] - offsety)*ratio[Y]);
	print_string(font_base, s_Date2.c_str());
	//## Memo ################################################################
	if (Bdd[j].flagMemoVisible) {
	  glRasterPos2f((Bdd[j].pos[X] + 10.0 + 200 - pos[X])*ratio[0], (1000.0 - stof(s_Date2)                     - pos[Y] - offsety)*ratio[Y]);
	  print_string(font_base, s_Memo.c_str());
	} } } } }
  
void bergson::afficherListe(){
  afficherListeDessin1 ();
  afficherListeDessin2 ();
  afficherListeTexte   ();
  gestionListe_affichageMenuHorizontal();
  gestionListe_affichageMenuVertical();
}

void bergson::interrogation(){
  /* Clear the window. */
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  afficherListe();
  if(!pause)
    {
      glutSwapBuffers();
      glutPostRedisplay();
    }
}

void bergson::my_handle_key(unsigned char key, int x, int y) {
  switch (key) {
  case 'a':    case 'A':   gestionListe_gestionCurseur(-1); break;
  case 'z':    case 'Z':   gestionListe_gestionCurseur(+1); break;
    
  case 'v':  case 'V': Bdd[posxCurseur].flagVisible = !Bdd[posxCurseur].flagVisible; break;
  case 'c':  case 'C': Bdd[posxCurseur].flagQuestionVisible = !Bdd[posxCurseur].flagQuestionVisible; break;
  case 'b':  case 'B': Bdd[posxCurseur].flagMemoVisible     = !Bdd[posxCurseur].flagMemoVisible; break;
    
  case '-':    offsety-=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;
  case '+':    offsety+=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;

  case 27:    exit(1);    break;
  case 'p':    case 'P':   pause = !pause;    break;
  case 's':    case 'S':   saveMetaData();    break;
  case 'l':    case 'L':   loadMetaData();    break;
  default:      break;
} }

bergson::bergson(int argc, char * argv[]): openGlInterface(argc, argv){
  posxCurseur=0;
  fileName = "metaData.save";
  fileNameListe = "listes/0-ListeDeListes.txt";
  //maListeDeListe.loadHumainDriver(fileNameListe);
  maListeDeListe.importDriver(fileNameListe);
  
  for (int i=0; i < maListeDeListe.size(); i++) {
    Bdd.push_back(maTableVide);
    Bdd.back().importDriver(maListeDeListe[i][0]);
    Bdd[i].color[R]            = stof(maListeDeListe[i][1]);
    Bdd[i].color[G]	       = stof(maListeDeListe[i][2]);
    Bdd[i].color[B]	       = stof(maListeDeListe[i][3]);
    Bdd[i].color[A]            = stof(maListeDeListe[i][4]);
    Bdd[i].pos[X]	       = stod(maListeDeListe[i][5]);
    Bdd[i].flagVisible         = stoi(maListeDeListe[i][6]);
    Bdd[i].flagQuestionVisible = stoi(maListeDeListe[i][7]);
    Bdd[i].flagMemoVisible     = stoi(maListeDeListe[i][8]);
  }
  glutKeyboardFunc(my_handle_key);

}

int bergson::loadMetaData() {
  ifstream in(fileName, std::ios::binary);
  in.unsetf(std::ios::skipws);
  
  RECORD   s_Lego;
  RECORD_F f_Lego;
  RECORD_I i_Lego;

  f_Lego.loadBinaire(&in);
  i_Lego.loadBinaire(&in);

  
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

  s_Lego.loadBinaire(&in);
  fileName          = s_Lego[0];
  cout << "fileName:" << fileName << endl;

  for (int i=0; i < Bdd.size(); i++) {
    RECORD_F f_Liste;
    RECORD_D d_Liste;
    RECORD_I i_Liste;

    f_Liste.loadBinaire(&in);
    d_Liste.loadBinaire(&in);
    i_Liste.loadBinaire(&in);

    Bdd[i].color[R]=		 f_Liste[0];
    Bdd[i].color[G]=	       	 f_Liste[1];
    Bdd[i].color[B]=	       	 f_Liste[2];
    Bdd[i].color[A]=             f_Liste[3];

    Bdd[i].pos[X]=		 d_Liste[0];
    Bdd[i].flagVisible=	         i_Liste[0];
    Bdd[i].flagQuestionVisible=  i_Liste[1];
    Bdd[i].flagMemoVisible=      i_Liste[2];
  }


  
  in.close();
  return true;
}

int bergson::saveMetaData() {
  ofstream out(fileName, std::ios::binary);
  out.unsetf(std::ios::skipws);
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
  i_Lego.saveBinaire(&out);
  
  s_Lego.push_back(fileName);
  s_Lego.saveBinaire(&out);
  

  for (int i=0; i < Bdd.size(); i++) {
    RECORD_F f_Liste;
    RECORD_D d_Liste;
    RECORD_I i_Liste;
    
    f_Liste.push_back(Bdd[i].color[R]);
    f_Liste.push_back(Bdd[i].color[G]);	       
    f_Liste.push_back(Bdd[i].color[B]);	       
    f_Liste.push_back(Bdd[i].color[A]);            
    d_Liste.push_back(Bdd[i].pos[X]);
    i_Liste.push_back(Bdd[i].flagVisible);
    i_Liste.push_back(Bdd[i].flagQuestionVisible);
    i_Liste.push_back(Bdd[i].flagMemoVisible);

    f_Liste.saveBinaire(&out);
    d_Liste.saveBinaire(&out);
    i_Liste.saveBinaire(&out);
  }

  out.close();
  return true;
}
