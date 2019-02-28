#include "main.hpp"
#include "pedagogie.hpp"

#include <iostream>
#include <string>
#include <cstring>

int main ( int argc, char * argv[]){
  pedagogie maPedagogie(argc, argv);
  //  maPedagogie.saveFile();
  maPedagogie.Hauptmenu();
}
