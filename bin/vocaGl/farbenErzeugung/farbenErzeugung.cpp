#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class farbe: public vector<float> {
  typename vector<float>::iterator it;
public:
  farbe() {
    float meineLeerSchwimmend = 0.0;
    for (int i=0; i<4; i++) this->push_back (meineLeerSchwimmend);
  }
  void print() {
    for (it=this->begin(); it!=this->end(); ++it) cout << *it << endl;
  }
  void print(unsigned int index) { cout << (*(this->begin()+index)); }
  float& operator [](int idx) {
    return vector<float>::data()[idx];
  }

};

class farbeTabelle: public vector<farbe> {
  typename vector<farbe>::iterator it;
public:
  farbe& operator [](int idx) {
    return vector<farbe>::data()[idx];
  }

  farbeTabelle(int taille) {
    farbe meineLeereFarbe;
    for (int i=0; i< taille; i++) {
      meineLeereFarbe.print();
//      meineLeereFarbe[0]=abs( sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) ) );
//      meineLeereFarbe[1]=abs( sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) ) );
//      meineLeereFarbe[2]=abs( sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) ) );

      meineLeereFarbe[0]=( 1 + sin( ((M_PI/3)*0) + ((M_PI / taille) * i ) ) ) / 2;
      meineLeereFarbe[1]=( 1 + sin( ((M_PI/3)*1) + ((M_PI / taille) * i ) ) ) / 2;
      meineLeereFarbe[2]=( 1 + sin( ((M_PI/3)*2) + ((M_PI / taille) * i ) ) ) / 2;
      meineLeereFarbe[3]= 1.0;
      push_back( meineLeereFarbe );
    }
  }
  int print() {
    for (it=this->begin(); it != this->end(); ++it)
      for (unsigned int j=0; j<4; j++)
	cout << "couleur" << "[" << j << "]:" << it->data()[j] << endl;
  }
};

int main() {
  farbeTabelle meineFarbenTabelle(10);
}
