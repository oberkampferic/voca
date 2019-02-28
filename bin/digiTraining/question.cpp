void master::question() {
  i_num = random() % i_limit;
  str_num = to_string(i_num);
  s_question = str_num;
}

//----------------------------------------------------------------------------------------------------

int master::reponse() {
  i_reponse= stoi(s_reponse);
}

//----------------------------------------------------------------------------------------------------

int master::jugement() {
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
}

//----------------------------------------------------------------------------------------------------



































void master::question2() {
  i_num = random() % (60*12);

  i_heures = i_num / 60;
  i_minutes = i_num - (i_heures * 60);

  cout << i_heures << " : " << i_minutes << " : " << i_num << endl;
  
  s_question = "Es ist ";
                                                                                                                
  if        ( i_minutes == 0 )  { s_question = s_question                                                                         + to_string ( i_heures     ) + " Uhr."; 
  } else if ( i_minutes == 30 ) { s_question = s_question                                                      + " halb "         + to_string ( i_heures + 1 ) + " Uhr."; 
  } else if ( i_minutes == 15 ) { s_question = s_question                                                      + " Viertel nach " + to_string ( i_heures     ) + " ."   ; 
  } else if ( i_minutes == 45 ) { s_question = s_question                                                      + " Viertel vor  " + to_string ( i_heures + 1 ) + " ."   ; 
  } else if ( i_minutes < 20 )  { s_question = s_question                    + to_string (      i_minutes    ) + " nach "         + to_string ( i_heures     ) + " ."   ;
  } else if ( i_minutes > 40 )  { s_question = s_question                    + to_string ( 60 - i_minutes    ) + " vor  "         + to_string ( i_heures + 1 ) + " ."   ;
  } else if ( i_minutes < 30 )  { s_question = s_question                    + to_string ( 30 - i_minutes    ) + " vor halb  "    + to_string ( i_heures + 1 ) + " ."   ;
  } else if ( i_minutes > 30 )  { s_question = s_question                    + to_string ( i_minutes - 30    ) + " nach halb "    + to_string ( i_heures + 1 ) + " ."   ;
  }

  cout << s_question << endl;
}

//----------------------------------------------------------------------------------------------------

int master::reponse2() {
  size_t pos1=0, pos2=0;

  pos2 = s_reponse.find(".", 0);
  cout << s_reponse.substr ( pos1, pos2-pos1 ) << "|" << pos1 << ":" << pos2 << endl;
  i_reponse  = stoi ( s_reponse.substr ( pos1, pos2-pos1 ));
  cout << s_reponse.substr ( pos2, s_reponse.size() - pos2);
  i_reponse2 = stoi ( s_reponse.substr ( pos2+1, s_reponse.size() - pos2 -1));
  cout << "Réponse:" << i_reponse << " : " << i_reponse2 << endl;
}

//----------------------------------------------------------------------------------------------------

int master::jugement2() {
  if ( (i_reponse == i_heures) && (i_reponse2 == i_minutes) ) {
    cout << "cbien!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!." << endl;
    i_reussite++;
  } else {
    cout << "######### => c pas bien, c'était " << i_heures << " : " << i_minutes << " .##########" << endl;
    cout << "On réécoute une fois." << endl;
    std::system (commandLine.c_str());
    cout << "Appuyez sur RETURN pour passer à la suite." << endl;
    cin >> s_reponse;
    i_echec++;
  }
}
