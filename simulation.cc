/*!
  \file   simulation.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module "simulation".
*/
#include <iostream>
#include <string>
#include <memory>
#include "simulation.h"
#include "textstorage.h"
#include "squarecell.h"
#include "constantes.h"
#include "fourmiliere.h"
#include "message.h"

using namespace std;

std::vector<std::shared_ptr<Entity>> loadFromFile(string path) {
    vector<shared_ptr<Entity>> entityList;
    vector<shared_ptr<Nourriture>> nourritureList;
    vector<shared_ptr<Fourmiliere>> fourmilliereList;
    importDump(readtxt(path), nourritureList, fourmilliereList);
    for(unsigned int i=0;i<fourmilliereList.size();i++){
        (*fourmilliereList[i]).check();
    }
    cout << message::success();
    return entityList;
}

void saveToFile(string path,std::vector<std::shared_ptr<Entity>> worldToDump) {
}