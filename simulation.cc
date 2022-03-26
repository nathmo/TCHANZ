/*!
  \file   simulation.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "simulation".
*/

#include "simulation.h"
#include "textstorage.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;
squarecell::Squarecell simulation::loadFromFile(string path) {
    vector<shared_ptr<squarecell::Entity>> entityList = textstorage::importDump(textstorage::readtxt(path));
    squarecell::Squarecell gridWorld = squarecell::Squarecell();
    for (auto entity = entityList.begin(); entity != entityList.end(); ++entity)
    {
        bool status = gridWorld.add((*entity));
        if(not status)
        {
            exit(0);
        }
    }
    //gridWorld.displayRawEntityGrid();
    return gridWorld;
}

void simulation::saveToFile(string path,squarecell::Squarecell worldToDump)
{

}