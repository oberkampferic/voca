
void openGlInterface::gestionListe_gestionCurseur(int Sens) {
  if ( Sens == -1 ) posxCurseur--; else posxCurseur++;
  if ( posxCurseur == -1 ) posxCurseur = maListeDeListe.size() -1;
  if ( posxCurseur >= maListeDeListe.size() ) posxCurseur=0;
}

void openGlInterface::gestionListe_rectangle(double x1, double y1, double x2, double y2) {
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

void openGlInterface::gestionListe_rectanglePlein(double x1, double y1, double x2, double y2) {
  glBegin(GL_QUADS);{
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
  }    glEnd();
}

void openGlInterface::gestionListe_affichageMenuHorizontal(){
  double x_debut,x_fin, x_delta, y_debut, y_fin, y_delta;
  double x_tailleFenetre, y_tailleFenetre;

  x_delta=glutGet(GLUT_WINDOW_WIDTH)-10;    x_debut=-(x_delta/2);      x_fin=x_delta/2;    
  y_delta=glutGet(GLUT_WINDOW_HEIGHT)-10;   y_debut=(y_delta/2);      y_fin=(y_delta/2)-30;    

  x_tailleFenetre = (x_delta / maListeDeListe.size());
  y_tailleFenetre = y_debut-y_fin;

  for (int i=0; i < maListeDeListe.size(); i++) {
    if (posxCurseur==i)
      glColor4f(Bdd[i].color[0]/1.5, Bdd[i].color[1]/1.5, Bdd[i].color[2]/1.5, Bdd[i].color[3]);
    else
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);

    gestionListe_rectanglePlein(x_debut+x_tailleFenetre*i, y_debut, x_debut+x_tailleFenetre*(i+1), y_fin);

    glColor4f(Bdd[i].color[0], Bdd[i].color[1], Bdd[i].color[2], Bdd[i].color[3]);
    glRasterPos2f( x_debut+x_tailleFenetre*i+10, (y_debut + y_fin)/2 );
    print_string( font_base, maListeDeListe[i][0].substr(12,maListeDeListe[i][0].length()-16).c_str() );
  }

  for (int i=0; i < maListeDeListe.size(); i++) {
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
  y_tailleFenetre = (y_delta / maListeDeListe.size());

  for (int i=0; i < maListeDeListe.size(); i++) {
    if (posxCurseur==i)
      glColor4f(Bdd[i].color[0]/1.5, Bdd[i].color[1]/1.5, Bdd[i].color[2]/1.5, Bdd[i].color[3]);
    else
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);

    gestionListe_rectanglePlein(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));

    glColor4f(Bdd[i].color[0], Bdd[i].color[1], Bdd[i].color[2], Bdd[i].color[3]);
    glRasterPos2f( x_debut+10, y_debut-(y_tailleFenetre*(i+0.5)) );
    
    print_string( font_base, maListeDeListe[i][0].substr(12,maListeDeListe[i][0].length()-16).c_str() );
  }

  for (int i=0; i < maListeDeListe.size(); i++) {
    if (posxCurseur==i) {
      glColor4f(Bdd[i].color[0]/2, Bdd[i].color[1]/2, Bdd[i].color[2]/2, Bdd[i].color[3]);
      gestionListe_rectangle(x_debut, y_debut-y_tailleFenetre*i, x_fin, y_debut-y_tailleFenetre*(i+1));
    }
  }
}
