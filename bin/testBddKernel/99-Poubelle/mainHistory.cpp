void fonction(DATABASE &maDatabase){
  fichier table2;
  table2.loadFichier("listeDeListe.txt");
  //  table2.loadFichier("Assimil");
  cout << "Debut###############" << endl;
  table2.print();
//  ofstream maSortie("Assimil.save");
//  table2.saveHumain(&maSortie);
  maDatabase.push_back(table2);
  cout << "Print Database" << endl;
  maDatabase.print();
  cout << "End print Database" << endl;
}


//Record
  RECORD monRecord("gnia1");
  monRecord.push_back("gnia2");
  monRecord.push_back("gnia2");
  monRecord.add("gnia4");
  monRecord.print();
  
  //Table
  TABLE table(monRecord);
  table.push_back(monRecord);
  table.add(monRecord);

  table.print();

  //Database
  DATABASE database;
  database.push_back( table );
  database.add( table );
  database.print();
  
//  //Rapport complet
//  database.print();
//
//  ofstream maSortie("nomfichier");
//  database.saveHumain(&maSortie);

//  DATABASE database2;
//  ifstream monEntree("nomfichier");
//  database2.import(&monEntree);

  fonction(database);

  cout << "Print vérification Database" << endl;
  database.print();
  cout << "End print vérification Database" << endl;


  cout << "Fin#################" << endl;
