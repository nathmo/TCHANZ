/*!
  \file   simulation.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module "simulation".
*/
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "simulation.h"
#include "textstorage.h"
#include "squarecell.h"
#include "message.h"
#include "entity.h"

using namespace std;

Simulation::Simulation() {
}

Simulation::Simulation(string path) {
    this->path = path;
}

void Simulation::setPath(std::string newpath){
    path = newpath;
}

vector<shared_ptr<Entity>> Simulation::getListEntity() {
    vector<shared_ptr<Entity>> entityToExport;
    entityToExport.insert(entityToExport.end(),nourritureList.begin(),
                                               nourritureList.end());
    entityToExport.insert(entityToExport.end(),anthillList.begin(),anthillList.end());
    return entityToExport;
}

void Simulation::loadFromFile() {
    nourritureList.clear(); // empty the memory to load the new array
    anthillList.clear();
    try {
        TextStorage::importTXT(path, nourritureList, anthillList);
        for (unsigned int i = 0; i < anthillList.size(); i++) {
            (*anthillList[i]).check();
        }
        cout << message::success();
    }
    catch (int code) {
        nourritureList = {};
        anthillList = {};
        return;
    }
}

void Simulation::saveToFile() {
    TextStorage::exportTXT(path, nourritureList, anthillList);
}

void Simulation::startHeadless() {
    loadFromFile();
    //Simulation::simulateStep(entityList);
    //Simulation::saveToFile(path+"Plus1Step",entityList);
}

void Simulation::simulateStep() {
    // create food randomly
    Squarecell::FullGrid();
    shared_ptr<Nourriture> food = Nourriture::randomCreate();
    vector<shared_ptr<Entity>> entityList;
    if(food != nullptr) {
        nourritureList.push_back(food);
    }
    entityList.insert(entityList.end(),nourritureList.begin(), nourritureList.end());
    entityList.insert(entityList.end(),anthillList.begin(), anthillList.end());
    for(auto entity:entityList) {
        entity->update(entityList);
        entity->draw();
    }
    for(unsigned int i=0;i<anthillList.size();i++) {
        if((anthillList[i])->getEnd_of_klan()) {
            anthillList.erase(anthillList.begin()+i);
        }
    }
}

int Simulation::getFoodNb() {
    return nourritureList.size();
}

int Simulation::getAnthNb() {
    return anthillList.size();
}

vector<int> Simulation::getAnthInfoStat(int id) {
    vector<int> stat;
    stat.push_back((*anthillList[id]).getfoodReserve());
    stat.push_back((*anthillList[id]).getnbC());
    stat.push_back((*anthillList[id]).getnbD());
    stat.push_back((*anthillList[id]).getnbP());
    return stat;
}