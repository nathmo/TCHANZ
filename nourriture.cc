/*!
  \file   nourriture.cc
  \author Nathann Morand (40%) et Felipe Ramirez (60%)
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/
#include <memory>
#include <iostream>
#include "nourriture.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Nourriture::Nourriture(Point position, int index) :
        Entity(position, 1, 1, nourritureCST, index) {}

shared_ptr<Nourriture> Nourriture::importFromExtSave(vector<string> &inputBuffer,
                                                     int index) {
    if(!(inputBuffer.size() <= 2)) {
        cout << "nourriture : number of argument mismatch" << endl;
        exit(0);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        if(Squarecell::checkOverlap(Point(x,y), 1, 1, nourritureCST)) {
            cout<< message::food_overlap(x,y);
            exit(EXIT_FAILURE);
        }
        return make_shared<Nourriture>(Point(x,y), index);
    }
}

void Nourriture::update(){
    cout << "updating the Nourriture with id "+to_string(id) << endl;
}

vector<vector<string>> Nourriture::export(){
    vector<vector<string>> toExport;
    cout << "exporting a nourriture" << endl;
    return toExport;
}

vector<vector<string>> Nourriture::export(
                                          vector<shared_ptr<Entity>> &listOfEntity)) {
    vector<vector<string>> vecVecStringFood;
    int count(0);

    for(unsigned int i(0); i < listOfEntity.size(); i++) {
        if((*listOfEntity[i])->getSpecie == nourritureCST) {
            count = count + 1;
        } else {
            break;
        }
    }

    vecVecStringFood.push_back(to_string(count));
    for(unsigned int i(0); i < count; i++) {
        int coordX = (((*listOfEntity[i]).getOccupiedSpace)->getPosition).getCoordX;
        int coordY = (((*listOfEntity[i]).getOccupiedSpace)->getPosition).getCoordY;
        string stringCoordX = to_string(coordX);
        string stringCoordY = to_string(coordY);

        vecVecStringFood.push_back({stringCoordX, stringCoordY});
    }

    return vecVecStringFood;
}