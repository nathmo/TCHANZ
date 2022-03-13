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
squarecell::Squarecell simulation::loadFromFile(string path) {
    cout << path << endl;
    vector<squarecell::Entity> entityList = textstorage::importDump(textstorage::readtxt(path));
    squarecell::Squarecell gridWorld = squarecell::Squarecell(gmax);
    for (auto entity = entityList.begin(); entity != entityList.end(); ++entity)
    {
        gridWorld.add(*entity);
    }
}
