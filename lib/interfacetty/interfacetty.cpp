#include "interfacetty.hpp"

void interfacetty::kurz(string message) {
  cout << message;
}

void interfacetty::message(string classe, string fonction, string message) {
  kurz( "message:" + classe + "::" + fonction + "():" + message + "\n");
}

void interfacetty::debug (string classe, string fonction, string message) {
  if (flagVerbose)
    kurz("debug:" + classe + "::" + fonction + "():" + message + "\n");
}

void interfacetty::erreur (string classe, string fonction, string message) {
  kurz( "erreur:" + classe + "::" + fonction + "():" + message + "\n");
  exit(0);
}

void interfacetty::erreur (string classe, string fonction, char** message) {
  kurz ("erreur:" + classe + "::" + fonction + "():");
  cout << message;
  kurz ("\n");
  exit(0);
}

