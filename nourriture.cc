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
        throw (-1);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        if(Squarecell::checkOverlap(Point(x,y), 1, 1, nourritureCST)) {
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
    return nullptr;
    return make_shared<Nourriture>(Point(x,y), index);
}

void Nourriture::update() {

}

vector<vector<string>> Nourriture::exportToString() {
    vector<vector<string>> vecVecStringFood;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    vecVecStringFood.push_back({x,y});
    return vecVecStringFood;
}

vector<vector<double>> Nourriture::draw() {
    vector<vector<double>> commandList;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();

    commandList = Squarecell::losange(x, y, 12);

    return commandList;
}