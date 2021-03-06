#include "freqFragment.hpp"

int main( int argc, char * argv[] ) {
  if (argc!=2) {
    //###################################################
////    vector<freqFragment> monVectorFf;
////
//    freqFragment test_Fragment ("test4.txt");
//
////    freqFragment dico_Francais; dico_Francais.traitementDico("dicoFrancaisBien.txt");
////    freqFragment dico_Allemand; dico_Allemand.traitementDico("dicoGermanAlleWortes.txt");
//
//    freqFragment dico_Allemand; dico_Allemand.traitementDico("dicoGermanAlleWortesPropre.txt");
//    freqFragment test_Fragment2; test_Fragment2.traitementDico("personnages.txt");
//    freqFragment test_Fragment3; test_Fragment3.traitementDico("connus.txt");
//    freqFragment test_Fragment4; test_Fragment4.traitementDico("2000.txt");
//    freqFragment test_Fragment5; test_Fragment5.traitementDico("20004000.txt");
//    freqFragment test_Fragment6; test_Fragment6.traitementDico("40006000.txt");
//    freqFragment test_Fragment7; test_Fragment7.traitementDico("60008000.txt");
//    freqFragment test_Fragment8; test_Fragment8.traitementDico("800010000.txt");
//
//    test_Fragment.substract(dico_Allemand);
//    test_Fragment.substract(test_Fragment2);
//    test_Fragment.substract(test_Fragment3);
//    test_Fragment.substract(test_Fragment4);
//    test_Fragment.substract(test_Fragment5);
//    test_Fragment.substract(test_Fragment6);
//    test_Fragment.substract(test_Fragment7);
//    test_Fragment.substract(test_Fragment8);
//    
//    //    dico_Allemand.print();
//    test_Fragment.print();

    freqFragment monTestFragment; //monTestFragment.traitementDico
    monTestFragment.load("dicoGrammaireBase.txt");          cerr << " loading."      << endl;
    monTestFragment.parsing();		                cerr << " parcing."      << endl;
    monTestFragment.store();		                cerr << " storage."      << endl;
    //    monTestFragment.sortAlphaSchnell();	                cerr << " tri."          << endl;
    //    monTestFragment.regroup();		                cerr << " regroupement." << endl;
    //    monTestFragment.deleteSqTerminaison();              cerr << " deleteTerm."   << endl;
    //        monTestFragment.print();
//
    freqFragment monTestFragmentM;
    monTestFragmentM.load("masculin");
    monTestFragmentM.parsing();		                cerr << " parcing."      << endl;
    monTestFragmentM.store();		                cerr << " storage."      << endl;
//    monTestFragmentM.sortAlphaSchnell();                cerr << " tri."          << endl;
//    monTestFragmentM.regroup();		                cerr << " regroupement." << endl;
//
    freqFragment monTestFragmentF;
    monTestFragmentF.load("feminin");
    monTestFragmentF.parsing();		                cerr << " parcing."      << endl;
    monTestFragmentF.store();		                cerr << " storage."      << endl;
//    monTestFragmentF.sortAlphaSchnell();                cerr << " tri."          << endl;
//    monTestFragmentF.regroup();		                cerr << " regroupement." << endl;
//
    freqFragment monTestFragmentN;
    monTestFragmentN.load("neutre");
    monTestFragmentN.parsing();		                cerr << " parcing."      << endl;
    monTestFragmentN.store();		                cerr << " storage."      << endl;
//    monTestFragmentN.sortAlphaSchnell();                cerr << " tri."          << endl;
//    monTestFragmentN.regroup();		                cerr << " regroupement." << endl;

    freqFragment monTestFragmentV;
    monTestFragmentV.load("verbe");
    monTestFragmentV.parsing();		                cerr << " parcing."      << endl;
    monTestFragmentV.store();		                cerr << " storage."      << endl;
//    monTestFragmentV.sortAlphaSchnell();                cerr << " tri."          << endl;
//    monTestFragmentV.regroup();		                cerr << " regroupement." << endl;
    

      monTestFragment.substract( monTestFragmentM );
          monTestFragment.save("sansM");
    monTestFragment.substract( monTestFragmentF );
          monTestFragment.save("sansF");
    monTestFragment.substract( monTestFragmentN );
          monTestFragment.save("sansN");
    monTestFragment.substract( monTestFragmentV );
          monTestFragment.save("sansV");
        monTestFragment.print();

  //###################################################
  } else {
    string nomFichier(argv[1]);
    freqFragment monFreqFragment(nomFichier);
    monFreqFragment.print();
  }
  //###################################################
}

