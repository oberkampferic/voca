#include <boost/algorithm/string.hpp>
//#include <stdlib>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;




class master{
public:
  
};


void refresh_limit() {
  
}

int main(void) {
  int flagVid[]={true,true,true,true,true};
  
  int i_num;  string str_num;
  int i_reponse;  string s_reponse;
  float ratio = 1.0;
  
  int i_limit=0, i_limitMax=0;
  int i_echec=0; int i_reussite=0; int i_totalReponse;
  float f_note=200.0, f_oldNote=200.0;
  string commandLine, commandLineCado;

  cout << "limite? ";
  cin >> i_limit;

  //désactiver les vidéos en trop
  if ( (i_limit>100) && flagVid[0] )     { flagVid[0]=false; }
  if ( (i_limit>1000) && flagVid[1] )    { flagVid[1]=false; }
  if ( (i_limit>10000) && flagVid[2] )   { flagVid[2]=false; }
  if ( (i_limit>100000) && flagVid[3] )  { flagVid[3]=false; }
  if ( (i_limit>1000000) && flagVid[4] ) { flagVid[4]=false; }










  //## BOUCLE ##################################################
  for(;;){
    i_num = random() % i_limit;
    str_num = to_string(i_num);
    
    commandLine =  "rm test.wav ; pico2wave -l de-DE -w test.wav " + str_num + " ; play test.wav treble 24 bass 10 gain -1 tempo -q -m -s -l " + to_string(ratio) + " 32.5153 15.1941 13.0061 > debugPlay 2>&1 &";
    std::system(commandLine.c_str());
    
    cout << "alors? ";
    cin >> s_reponse;
    i_reponse= stoi(s_reponse);

    //Jugement--------------------------------------------------
    if (i_reponse==i_num) {
      cout << "cbien!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!." << endl;
      i_reussite++;
    } else {
      cout << "######### => c pas bien, c'était " << str_num << " .##########" << endl;
      cout << "On réécoute une fois." << endl;
      std::system (commandLine.c_str());
      cout << "Appuyez sur RETURN pour passer à la suite." << endl;
      cin >> s_reponse;
      i_echec++;
    }
    
    //Digne de passer à la suite?------------------------------
    i_totalReponse = i_reussite + i_echec;

    f_oldNote = f_note;
    if (i_totalReponse>0)
      f_note = ( (float) i_reussite / (float) i_totalReponse ) * 200.0;

    
    if ( f_note >= f_oldNote ) { i_limit *=1.2; ratio*=1.05;     }
    else                       { i_limit /=1.2; ratio/=1.05;     }
    if ( ratio > 1.0 )  ratio=1.0;
    //    if ( f_note >= 200) ratio=1.0;

    cout << "NOTE: " << f_note << " / 200. $$$$$$$$$$$$$$$$$$$$ i_réussite: " << i_reussite << " échecs: " << i_echec << " total: " << i_limit << " ratio: " << ratio << endl;
    //---carotte-----------------------------------------------
    if ( (i_limit>100) && flagVid[0] ) { commandLineCado = "vlc --fullscreen --play-and-exit .fusee1.mp4"; std::system(commandLineCado.c_str()); flagVid[0]=false; }
    if ( (i_limit>1000) && flagVid[1] ) { commandLineCado = "vlc --fullscreen --play-and-exit .fusee2.mp4"; std::system(commandLineCado.c_str()); flagVid[1]=false; }
    if ( (i_limit>10000) && flagVid[2] ) { commandLineCado = "vlc --fullscreen --play-and-exit .fusee3.mp4"; std::system(commandLineCado.c_str()); flagVid[2]=false; }
    if ( (i_limit>100000) && flagVid[3] ) { commandLineCado = "vlc --fullscreen --play-and-exit .fusee4.mp4"; std::system(commandLineCado.c_str()); flagVid[3]=false; }
    if ( (i_limit>1000000) && flagVid[4] ) { commandLineCado = "vlc --fullscreen --play-and-exit .fusee5.mp4"; std::system(commandLineCado.c_str()); flagVid[4]=false; cout << "C'est bon, vous savez parler couramment allemand. Au revoir!" << endl; exit(true); }

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
}
