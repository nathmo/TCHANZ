/*!
  \file   simulation.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "simulation".
*/

#include "simulation.h"
#include "textstorage.h"
#include "squarecell.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

std::vector<std::shared_ptr<entity::Entity>> simulation::loadFromFile(string path) {
    vector<shared_ptr<entity::Entity>> entityList(textstorage::importDump(textstorage::readtxt(path)));
    return entityList;
}

void simulation::saveToFile(string path,std::vector<std::shared_ptr<entity::Entity>> worldToDump) {

}