void openGlInterface::my_motionMouse(int x, int y) {
  float delta[2];
  
  if (Kartebewegung==1) {    //déplacement de l'ensemble de la map
    delta[X]=old[X]-x;
    delta[Y]=old[Y]-y;
    pos[X]+=delta[X]/ratio[X];
    pos[Y]-=delta[Y]/ratio[Y];
    old[X]=x; old[Y]=y;
  }
  if (Spaltebewegung==1) {   //déplacement de la colonne dont
    delta[X]=old[X]-x;
    ServerBdd[posyCurseur][nearestTableIndex].pos[X]-=delta[X]/ratio[X];
    old[X]=x;
  }

  activerAffichage=true; 
}

void openGlInterface::my_motionMousePassive(int x, int y) {
  float delta[2];
  colonneConcernee(x, y);
  einfugemarkewort=motConcerne(x,y);	//Identifier quel est le mot le plus proche.
  if (Kartebewegung==1) {    //déplacement de l'ensemble de la map
    delta[X]=old[X]-x;
    delta[Y]=old[Y]-y;
    pos[X]+=delta[X]/ratio[X];
    pos[Y]-=delta[Y]/ratio[Y];
    old[X]=x; old[Y]=y;
  }
  if (Spaltebewegung==1) {   //déplacement de la colonne dont
    delta[X]=old[X]-x;
    ServerBdd[posyCurseur][nearestTableIndex].pos[X]-=delta[X]/ratio[X];
    old[X]=x;
  }
  if (!modeEco) activerAffichage=true; 
}


void openGlInterface::wortVerlagerung(int sens) {
  int prochaineTableIndex;
    if ( (indexErstWort != -1) && (indexLetztWort != -1) ) {
      if (ServerBdd[posyCurseur].size()>1) { //une seule table?
	if (sens==0) {
	  if ((nearestTableIndex) < (ServerBdd[posyCurseur].size()-1)) prochaineTableIndex = nearestTableIndex+1;
	  else                                                         prochaineTableIndex = 0;
	} else {
	  if (nearestTableIndex == 0)       prochaineTableIndex=  (ServerBdd[posyCurseur].size()-1);
	  else                   	    prochaineTableIndex = nearestTableIndex-1;
	}
	for (int i= indexErstWort; i<= indexLetztWort; i++) {
	  ServerBdd[posyCurseur][prochaineTableIndex].push_back( ServerBdd[posyCurseur][nearestTableIndex][(int) indexErstWort] );
	  ServerBdd[posyCurseur][nearestTableIndex].erase(ServerBdd[posyCurseur][nearestTableIndex].begin()+(int) indexErstWort);
	}
      }
    }
}

void openGlInterface::my_mouse(int button, int state, int x, int y) {
  string s_radical;
  int mod=glutGetModifiers();
  long widthSur2= glutGet(GLUT_WINDOW_WIDTH)/2;
  long heightSur2= glutGet(GLUT_WINDOW_HEIGHT)/2;

  colonneConcernee(x, y);
  int projY=motConcerne(x,y);	//Identifier quel est le mot le plus proche.
  //recherche Dico de ce mot
  
  if (state==GLUT_DOWN){
    if (projY!=-1) {  //Il y a bien un mot concerné? 
      cout << ServerBdd[posyCurseur][nearestTableIndex][(int) projY][0] << " <=> "
	   << ServerBdd[posyCurseur][nearestTableIndex][(int) projY][1] << "##################" << endl;

      if (!modeEco) {
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
  }
  //### DEPLACEMENT MOT ###########################################
  switch(button) {
  case GLUT_LEFT_BUTTON: //########################################
    if (state==GLUT_DOWN) {
      indexErstWort=projY;   //Verlagung eines Wortreihe: Bestimmung des ersten wortes
      if (projY!=-1) {
	if (glutGetModifiers() & GLUT_ACTIVE_ALT) {    // Alt aktiv.
	  Wortreihebewegung=0;
	  Spaltebewegung=0;
	  Kartebewegung=1;     //Einschaltung der Kartebewegung
	} else {                                       // Alt inaktiv
	  Wortreihebewegung=1;
	  Spaltebewegung=0;
	  Kartebewegung=0;     //Aufschaltung der Kartebewegung
	}
      } else {
	Wortreihebewegung=0;
	Spaltebewegung=0;
	Kartebewegung=1;     //Einschaltung der Kartebewegung
      }
    }

    if (state==GLUT_UP) {
      indexLetztWort=projY;  //Verlagung eines Wortreihe: Bestimmung des letzen wortes
      if ( (projY!=-1) && !(glutGetModifiers() & GLUT_ACTIVE_ALT) ) 
	wortVerlagerung(LINKS);
      Wortreihebewegung=0;
      Spaltebewegung=0;
      Kartebewegung=0;     //Aufschaltung der Kartebewegung
    }
    old[X]=x; old[Y]=y;
    break;

  case GLUT_RIGHT_BUTTON://########################################
    if (state==GLUT_DOWN){ //Einschaltung der Bewegung einer Spalte
      indexErstWort=projY;   //Verlagung eines Wortreihe: Bestimmung des ersten wortes
      if (glutGetModifiers() & GLUT_ACTIVE_ALT) {    // Alt aktiv.
	Wortreihebewegung=0;  //Ya.
	Spaltebewegung=1; cout << "Spaltebewegung=1" << endl;
	Kartebewegung=0;
      } else {
	if (projY!=-1) {       //Ist ein wort betrifft?
	  Wortreihebewegung=1;  //Ya.
	  Spaltebewegung=0;cout << "Spaltebewegung=0"<< endl;
	  Kartebewegung=0;
	} else {
	  Wortreihebewegung=0;  //Nein.
	  Spaltebewegung=1;     //So verlagern wir eine spalte.
	  Kartebewegung=0;  cout << "Spaltebewegung=1"<< endl;
	}
      }
    }
    if (state==GLUT_UP) {  //Déplacement d'une série de mots 
      indexLetztWort=projY;       // il y a bien un mot concerné?
      if ( (!(glutGetModifiers() & GLUT_ACTIVE_ALT)) && (projY!=-1) )
	wortVerlagerung(RECHTS);

      Wortreihebewegung=0;
      Spaltebewegung=0;cout << "Spaltebewegung=0"<< endl;
      Kartebewegung=0;
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
