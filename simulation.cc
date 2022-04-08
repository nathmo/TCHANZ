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

vector<shared_ptr<Entity>> Simulation::loadFromFile(string path) {
    vector<shared_ptr<Entity>> entityList;
    vector<shared_ptr<Nourriture>> nourritureList;
    vector<shared_ptr<Fourmiliere>> anthillList;
    try {
        TextStorage::importTXT(path, nourritureList, anthillList);
        for (unsigned int i = 0; i < anthillList.size(); i++) {
            (*anthillList[i]).check();
        }
        cout << message::success();
        entityList.insert(entityList.end(),
                          nourritureList.begin(), nourritureList.end());
        entityList.insert(entityList.end(), anthillList.begin(), anthillList.end());
        return entityList;
    }
    catch (int code){
        return entityList;
    }
}

void Simulation::saveToFile(string path, vector<shared_ptr<Entity>> worldToDump) {

}

void Simulation::startHeadless(string path) {
    vector<shared_ptr<Entity>> entityList = Simulation::loadFromFile(path);
    //Simulation::simulateStep(entityList);
    //Simulation::saveToFile(path+"Plus1Step",entityList);
}

void Simulation::simulateStep(vector<shared_ptr<Entity>> entityList){
    for(auto entity:entityList){
        entity->update();
    }
}