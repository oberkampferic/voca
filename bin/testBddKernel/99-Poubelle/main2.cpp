#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T> 
class element: public vector<T> {
public:
  T maVal;
  element(){};
  ~element(){};

//  T& operator [](int idx) {
//    T
//    return this->data;
//  }

  T& operator [](int idx) {
    T* p = vector<T>::data();

    maVal = p[idx];

    return p[idx]; //element[idx];
    return vector<T>::data()[idx];
    //return element[idx];
  }
};

int main (int argc, char * argv[]) {
  
  element<string> elementString;
  elementString.push_back("gnia");
  cout << elementString[0] << endl;
  
  string test;
  test=elementString[0];
  
  elementString[0].assign("gnia2");
  test=elementString[0];
  cout << "test2:" << test << endl;

  elementString[0]="gnia3gnia";
  cout << elementString[0] << endl;

  //########################################
  // plus compliqué
  //########################################

  element<element> maTable; //table de record, puisque element est un vecteur de string
  
  
  return 0;
}
