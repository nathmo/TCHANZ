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

Simulation::Simulation(){
}

Simulation::Simulation(string path){
    this->path = path;
}

void Simulation::loadFromFile() {

    try {
        TextStorage::importTXT(path, nourritureList, anthillList);
        for (unsigned int i = 0; i < anthillList.size(); i++) {
            (*anthillList[i]).check();
        }
        cout << message::success();
    }
    catch (int code){
        return;
    }
}

void Simulation::saveToFile() {

}

void Simulation::startHeadless() {
    loadFromFile();
    //Simulation::simulateStep(entityList);
    //Simulation::saveToFile(path+"Plus1Step",entityList);
}

void Simulation::simulateStep(){
    for(auto entity:anthillList){
        entity->update();
    }
}