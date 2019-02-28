#ifndef MASTER_HPP
#define MASTER_HPP

using namespace std;


class master{
private:
  int i_minutes, i_heures;

  int i_num;  string str_num;
  string s_question;
  int i_reponse;  int i_reponse2; string s_reponse;
  float ratio = 1.0;
  
  int i_limit=0, i_limitMax=0;
  int i_echec=0; int i_reussite=0; int i_totalReponse;
  float f_note=200.0, f_oldNote=200.0;
  string commandLine, commandLineCado;
  int flagVid[5];
  

public:
  void refresh_limit();
  master();
  
  void cado(string fileName);
  
  void question();
  int  reponse ();
  int  jugement ();
  
  void question2();
  int  reponse2 ();
  int  jugement2 ();
  
  void tableauDeBord();

  int questionnaire ();
};



#include "master.cpp"
  

#endif
