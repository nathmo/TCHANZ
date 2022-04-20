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

void Nourriture::update(vector<shared_ptr<Entity>> & entityList) {

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

/*
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    int negBias = (-g_max*resolution/2+1);
    float sinBias = 0.353553391;
    float largeur = 0.707106781;
    // draw white diamond
    cr->set_source_rgb(1, 1, 1);
    cr->set_line_width(largeur*(resolution));
    cr->move_to((x)*resolution+negBias+1, (y)*resolution+negBias+1);
    cr->line_to((x+1-sinBias)*resolution+negBias,(y+1-sinBias)*resolution+negBias);
    cr->stroke();
}
 */