/*!
  \file   projet.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module principal avec la fonction main()
*/
#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2) { // delete once GUI is setup

        cout << "Please provide a file to load" << endl;
        return 0;
    }
    vector<shared_ptr<Entity>> entityVect(loadFromFile(string(argv[1])));
    return 0;
}