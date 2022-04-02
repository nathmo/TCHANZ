/*!
  \file   projet.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module principal avec la fonction main()
*/
#include "simulation.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "Please provide a file to load" << endl;
        return 0;
    }
    Simulation::startHeadless(argv[1]);
    return 0;
}