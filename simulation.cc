/*!
  \file   simulation.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "simulation".
*/

#include "simulation.h"
#include "textstorage.h"
#include <iostream>

using namespace std;
void simulation::loadFromFile(string path) {
    cout << path << endl;
    textstorage::readtxt(path);
}
