/*!
  \file   nourriture.cc
  \author Nathann Morand (40%) et Felipe Ramirez (60%)
  \date   MARS 2022
  \brief  implémentation du module "nourriture".
*/
#include <memory>
#include <iostream>
#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>
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

void Nourriture::update(){
    cout << "updating the Nourriture with id "+to_string(id) << endl;
}

vector<vector<string>> Nourriture::exportToString() {
    vector<vector<string>> vecVecStringFood;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    vecVecStringFood.push_back({x,y});
    return vecVecStringFood;
}

void Nourriture::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    // draw white diamond
    cr->set_source_rgb(1, 1, 1);
    cr->set_line_width(1);

    cr->move_to((x+0.5)*resolution, y*resolution);
    cr->line_to((x)*resolution,(y+0.5)*resolution);

    cr->move_to((x)*resolution,(y+0.5)*resolution);
    cr->line_to((x+0.5)*resolution,(y+1)*resolution);

    cr->move_to((x+0.5)*resolution,(y+1)*resolution);
    cr->line_to((x+1)*resolution,(y+0.5)*resolution);

    cr->move_to((x+1)*resolution,(y+0.5)*resolution);
    cr->line_to((x+0.5)*resolution, y*resolution);
    cr->fill_preserve(); // might fill out the shape
    cr->stroke();
}