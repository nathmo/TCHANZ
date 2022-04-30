/*!
  \file   nourriture.cc
  \author Nathann Morand (40%) et Felipe Ramirez (60%)
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/
#include <memory>
#include <vector>
#include <iostream>
#include "nourriture.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Nourriture::Nourriture(Point position, int index) :
        Entity(position, 1, 1, nourritureCST, index, true) {}

shared_ptr<Nourriture> Nourriture::importFromExtSave(vector<string> &inputBuffer,
                                                     int index) {
    if(!(inputBuffer.size() <= 2)) {
        cout << "nourriture : number of argument mismatch" << endl;
        throw (-1);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        if(Squarecell::checkOverlap(Point(x,y), 1, 1, nourritureCST, true)) {
            cout<< message::food_overlap(x,y);
            throw (-1);
        }
        return make_shared<Nourriture>(Point(x,y), index);
    }
}

shared_ptr<Nourriture> Nourriture::randomCreate() {
    int x = 0;
    int y = 0;
    int index = -1;
    if(Entity::biasedCoinFlip(food_rate)) {
        for(int i=0;i<max_food_trial;i++) {
            x = Entity::randInt(1,g_max-2);
            y = Entity::randInt(1,g_max-2);
            bool occupied = Squarecell::checkOverlap(Point(x,y), 1, 1, allCST, true);
            if(not occupied) {
                return make_shared<Nourriture>(Point(x,y), index);
            }
        }
    }
    return nullptr;
}

void Nourriture::update(vector<shared_ptr<Entity>> &entityList) {

}

vector<vector<string>> Nourriture::exportToString() {
    vector<vector<string>> vecVecStringFood;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    vecVecStringFood.push_back({x,y});
    return vecVecStringFood;
}

void Nourriture::draw() {
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();

    Squarecell::losange(x, y, 12);
}
