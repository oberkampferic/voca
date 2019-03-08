#include "farbe.hpp"

farbe::farbe() {
  float meineLeerSchwimmend = 0.0;
  for (int i=0; i<4; i++) this->push_back (meineLeerSchwimmend);
}

void farbe::print(void) {
  for (it=this->begin(); it!=this->end(); ++it) cout << *it << endl;
}

void farbe::print(unsigned int index) { cout << (*(this->begin()+index)); }

//==================================================

farbeTabelle::farbeTabelle(int taille, unsigned int typeAlgo, float ratio) {
  farbe meineLeereFarbe;
  for (int i=0; i< taille; i++) {
    //      meineLeereFarbe.print();
    switch (typeAlgo%3) {
    case 0:
      meineLeereFarbe[0]=abs( sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) ) );
      meineLeereFarbe[1]=abs( sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) ) );
      meineLeereFarbe[2]=abs( sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) ) );
      break;
    case 1:
      meineLeereFarbe[0]=( 1 + sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) )) / 2;
      meineLeereFarbe[1]=( 1 + sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) )) / 2;
      meineLeereFarbe[2]=( 1 + sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) )) / 2;
      break;
    case 2:
      meineLeereFarbe[0]=( 1 + sin( (((M_PI/3)*0) + ((M_PI / taille) * i ) )*2 )) / 2;
      meineLeereFarbe[1]=( 1 + sin( (((M_PI/3)*1) + ((M_PI / taille) * i ) )*2 )) / 2;
      meineLeereFarbe[2]=( 1 + sin( (((M_PI/3)*2) + ((M_PI / taille) * i ) )*2 )) / 2;
      break;
    }
    meineLeereFarbe[0]*= ratio;
    meineLeereFarbe[1]*= ratio;
    meineLeereFarbe[2]*= ratio;
      
    meineLeereFarbe[3]= 0.5;
    push_back( meineLeereFarbe );
  }
}

int farbeTabelle::print() {
  for (it=this->begin(); it != this->end(); ++it)
    for (unsigned int j=0; j<4; j++)
      cout << "couleur" << "[" << j << "]:" << it->data()[j] << endl;
}



