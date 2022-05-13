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

vector<shared_ptr<Entity>> Simulation::getListEntity() {
    vector<shared_ptr<Entity>> entityToExport;
    entityToExport.insert(entityToExport.end(),nourritureList.begin(),
                          nourritureList.end());
    entityToExport.insert(entityToExport.end(),anthillList.begin(),anthillList.end());
    return entityToExport;
}

void Simulation::loadFromFile(string path) {
    nourritureList.clear(); // empty the memory to load the new array
    anthillList.clear();
    try {
        TextStorage::importTXT(path, nourritureList, anthillList);
        for(unsigned int i = 0; i < anthillList.size(); i++) {
            (*anthillList[i]).check();
        }
        cout << message::success();
    }
    catch(int code) {
        nourritureList = {};
        anthillList = {};
        return;
    }
}

void Simulation::saveToFile(string path) {
    TextStorage::exportTXT(path, nourritureList, anthillList);
}

void Simulation::simulateStep() {
    vector<shared_ptr<Entity>> entityList;
    shared_ptr<Nourriture> food = Nourriture::randomCreate();

    if(food != nullptr) {
        nourritureList.push_back(food);
        cout << "random food generated : "<<(*food).getPosition().getCoordX() <<" "<<(*food).getPosition().getCoordY()  << endl;
    }// create food randomly
    entityList.insert(entityList.end(),nourritureList.begin(), nourritureList.end());
    entityList.insert(entityList.end(),anthillList.begin(), anthillList.end());
    for(auto anthill:anthillList) {
        vector<shared_ptr<Fourmi>> fourmiList = (anthill->getAnts());
        entityList.insert(entityList.end(),fourmiList.begin(), fourmiList.end());
    }// update the anthill and their ants
    for(auto anthill:anthillList) {
        cout << "updating anthill : "<<anthill->getId()<< endl;
        anthill->update(entityList);
    }// update the anthill and their ants
    for(unsigned int i=0;i<anthillList.size();i++) {
        if((anthillList[i])->getEndOfLife()) {
            cout << "erasing anthill : "<<anthillList[i]->getId()<< endl;
            anthillList.erase(anthillList.begin()+i);
        }
    }// erase anthill that died
    for(unsigned int i=0;i<nourritureList.size();i++) {
        if((nourritureList[i])->getEndOfLife()) {
            cout << "erasing food : "<<nourritureList[i]->getId()<< endl;
            nourritureList.erase(nourritureList.begin()+i);
        }// erase food that where picked up
    }
}

void Simulation::refreshGUI() {
    Squarecell::FullGrid(); // draw the grid
    vector<shared_ptr<Entity>> entityList;
    entityList.insert(entityList.end(),nourritureList.begin(), nourritureList.end());
    entityList.insert(entityList.end(),anthillList.begin(), anthillList.end());
    for(auto entity:entityList) {
        entity->draw();// draw the entity
    }
}

int Simulation::getFoodNb() {
    return nourritureList.size();
}

int Simulation::getAnthNb() {
    return anthillList.size();
}

vector<double> Simulation::getAnthInfoStat(int id) {
    vector<double> stat;
    stat.push_back((*anthillList[id]).getFood());
    stat.push_back((*anthillList[id]).getnbC());
    stat.push_back((*anthillList[id]).getnbD());
    stat.push_back((*anthillList[id]).getnbP());
    return stat;
}