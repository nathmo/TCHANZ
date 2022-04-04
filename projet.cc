/*!
  \file   projet.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module principal avec la fonction main()
*/

#include <iostream>
#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "Please provide a file to load" << endl;
        Gui::window();
        return 0;
    }
    Simulation::startHeadless(argv[1]); // for now, No GUI
    return 0;
}