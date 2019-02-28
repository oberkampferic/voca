
void master::refresh_limit() {
  //désactiver les vidéos en trop
  if ( (i_limit>100) && flagVid[0] )     { flagVid[0]=false; }
  if ( (i_limit>1000) && flagVid[1] )    { flagVid[1]=false; }
  if ( (i_limit>10000) && flagVid[2] )   { flagVid[2]=false; }
  if ( (i_limit>100000) && flagVid[3] )  { flagVid[3]=false; }
  if ( (i_limit>1000000) && flagVid[4] ) { flagVid[4]=false; }
}

//####################################################################################################

master::master() {
  for (int i=0; i<5; i++) flagVid[i]=true;

  cout << "initialisation avec un nombre? ";
  cin >> i_limit;

  i_num = random() % 100;
  
  refresh_limit();
}

//####################################################################################################

void master::cado( string fileName) {
  commandLineCado = "vlc --fullscreen --play-and-exit " + fileName;
  std::system(commandLineCado.c_str());
}
  
//####################################################################################################

#include "question.cpp"

//####################################################################################################

void master::tableauDeBord() {
  cout << "NOTE: " << f_note << " / 200. $$$$$$$$$$$$$$$$$$$$ i_réussite: " << i_reussite << " échecs: " << i_echec << " score: " << i_limit << " ratio: " << ratio << endl;
  for(int i=0; i<5; i++) cout << flagVid[i] << "\t"; cout << endl;
}

//####################################################################################################

int master::questionnaire  () {

  question2();
  
  commandLine =  "rm test.wav ; pico2wave -l de-DE -w test.wav \"" + s_question + "\" ; play test.wav treble 24 bass 0 gain -1 tempo -q -m -s -l " + to_string(ratio) + " 32.5153 15.1941 13.0061 > debugPlay 2>&1 &";
  cout << commandLine << endl;
  std::system(commandLine.c_str());
    
  cout << "alors? ";
  cin >> s_reponse;

  reponse2();


  jugement2();
  
  //Digne de passer à la suite?------------------------------
  i_totalReponse = i_reussite + i_echec;

  f_oldNote = f_note;
  if (i_totalReponse>0)
    f_note = ( (float) i_reussite / (float) i_totalReponse ) * 200.0;
  if ( f_note >= f_oldNote ) { i_limit *=1.2; ratio*=1.05;     }
  else                       { i_limit /=1.2; ratio/=1.05;     }
  if ( ratio > 1.0 )  ratio=1.0;

  tableauDeBord();

  //---carotte-----------------------------------------------
  if ( (i_limit>100)     && flagVid[0] ) { cado( ".fusee1.mp4");  }
  if ( (i_limit>1000)    && flagVid[1] ) { cado( ".fusee2.mp4");  }
  if ( (i_limit>10000)   && flagVid[2] ) { cado( ".fusee3.mp4");  }
  if ( (i_limit>100000)  && flagVid[3] ) { cado( ".fusee4.mp4");  }
  if ( (i_limit>1000000) && flagVid[4] ) { cado( ".fusee5.mp4");  cout << "C'est bon, vous savez parler couramment allemand. Au revoir!" << endl; exit(true); }
  refresh_limit();

  //fin?
  if (i_limit>i_limitMax) i_limitMax = i_limit;
  //    if (f_note<100) {
  //      cout << "Bon, je crois que l'on a bien travaillé aujourd'hui, il est temps d'aller faire une sieste. On se revoit la semaine prochaine?" << endl;
  //      cout << "A propos, vous avez atteint un score maximum de " + to_string(i_limitMax) + " points." << endl;
  //      exit(false);
  //    }
  //laxisme
  if ( (i_reussite+i_echec) > 10) {
    i_reussite--;
    i_echec--;
  };
  if (i_reussite==-1) i_reussite=0;
  if (i_echec==-1) i_echec=0;
}
