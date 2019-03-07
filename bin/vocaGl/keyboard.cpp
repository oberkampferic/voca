switch (tastatur) {
 case TASTATUR_FRANCAIS:
   switch (key) {
   case 'k': case 'K': tastatur = TASTATUR_DEUTSCH; break;
   case 'a': case 'A': gestionListe_gestionCurseurX(-1); break;
   case 'z': case 'Z': gestionListe_gestionCurseurX(+1); break;
   case 'w': case 'W': gestionListe_gestionCurseurY(-1); break;
   case 'x': case 'X': gestionListe_gestionCurseurY(+1); break;
    
   case 'v': case 'V': ServerBdd[posyCurseur][posxCurseur].flagVisible         = !ServerBdd[posyCurseur][posxCurseur].flagVisible; break;
   case 'c': case 'C': ServerBdd[posyCurseur][posxCurseur].flagQuestionVisible = !ServerBdd[posyCurseur][posxCurseur].flagQuestionVisible; break;
   case 'n': case 'N':
     maTableVide2.filename = "Tabelle " + to_string ( ServerBdd[posyCurseur].size() );
     ServerBdd[posyCurseur].push_back(maTableVide2);
     break;
   case 'b': case 'B': ServerBdd[posyCurseur][posxCurseur].flagMemoVisible     = !ServerBdd[posyCurseur][posxCurseur].flagMemoVisible; break;
    
   case 'e': case 'E': idFont--; init_font (font_base, "fixed", idFont); break;
   case 'r': case 'R': idFont++; init_font (font_base, "fixed", idFont); break;
   case 'd': case 'D': idFont-=10; init_font (font_base, "fixed", idFont); break;
   case 'f': case 'F': idFont+=10; init_font (font_base, "fixed", idFont); break;
   case 't': case 'T': idFont-=100; init_font (font_base, "fixed", idFont); break;
   case 'y': case 'Y': idFont+=100; init_font (font_base, "fixed", idFont); break;

   case 'o': case 'O': einfugemarkefarbe--; break;
   case 'p': case 'P': einfugemarkefarbe++; break;
    
   case '-': offsety-=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;
   case '+': offsety+=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;

   case 27:              exit(1);           break;
   case 's': case 'S':   saveMetaData();    break;
   case 'l': case 'L':   loadMetaData();    break;
   default:  break;
   } break;

 case TASTATUR_DEUTSCH:
   switch (key) {
   case 'k': case 'K': tastatur = TASTATUR_FRANCAIS; break;
   case 'q': case 'Q': gestionListe_gestionCurseurX(-1); break;
   case 'w': case 'W': gestionListe_gestionCurseurX(+1); break;
   case 'y': case 'Y': gestionListe_gestionCurseurY(-1); break;
   case 'x': case 'X': gestionListe_gestionCurseurY(+1); break;
    
   case 'v': case 'V': ServerBdd[posyCurseur][posxCurseur].flagVisible         = !ServerBdd[posyCurseur][posxCurseur].flagVisible; break;
   case 'c': case 'C': ServerBdd[posyCurseur][posxCurseur].flagQuestionVisible = !ServerBdd[posyCurseur][posxCurseur].flagQuestionVisible; break;
   case 'n': case 'N':
     maTableVide2.filename = "Tabelle " + to_string ( ServerBdd[posyCurseur].size() );
     ServerBdd[posyCurseur].push_back(maTableVide2);
     break;
   case 'b': case 'B': ServerBdd[posyCurseur][posxCurseur].flagMemoVisible     = !ServerBdd[posyCurseur][posxCurseur].flagMemoVisible; break;
    
   case 'e': case 'E': idFont--; init_font (font_base, "fixed", idFont); break;
   case 'r': case 'R': idFont++; init_font (font_base, "fixed", idFont); break;
   case 'd': case 'D': idFont-=10; init_font (font_base, "fixed", idFont); break;
   case 'f': case 'F': idFont+=10; init_font (font_base, "fixed", idFont); break;
   case 't': case 'T': idFont-=100; init_font (font_base, "fixed", idFont); break;
   case 'z': case 'Z': idFont+=100; init_font (font_base, "fixed", idFont); break;

   case '0':           if (modeEco) modeEco=false; else modeEco = true; break;
   case 'o': case 'O': einfugemarkefarbe--; break;
   case 'p': case 'P': einfugemarkefarbe++; break;
    
   case '-': offsety-=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;
   case '+': offsety+=((glutGetModifiers()==GLUT_ACTIVE_SHIFT)?0.3:0.1);    break;

   case 27:              exit(1);           break;
   case 's': case 'S':   saveMetaData();    break;
   case 'l': case 'L':   loadMetaData();    break;
   default:  break;
   } break;
 default:
   tastatur= TASTATUR_DEUTSCH;
   break;
 }

