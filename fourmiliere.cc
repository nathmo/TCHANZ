/*!
  \file   fourmiliere.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/
#include <iostream>
#include <memory>
#include <string>
#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>
#include "fourmiliere.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"
#include "graphic.h"

using namespace std;

Fourmiliere::Fourmiliere(Point position, int size, int totalFood,
                         int nbC, int nbD, int nbP, int id,
                         vector<shared_ptr<Fourmi>> FourmiList) :
                         Entity(position,size, size,fourmilliereCST, id) {
    foodReserve = totalFood;
    this->nbC=nbC;
    this->nbD=nbD;
    this->nbP=nbP;
    memberAnts = FourmiList;
    end_of_klan = false;
}

int Fourmiliere::getnbC(){
    return nbC;
}

int Fourmiliere::getnbD(){
    return nbD;
}

int Fourmiliere::getnbP(){
    return nbP;
}

int Fourmiliere::getfoodReserve(){
    return foodReserve;
}

bool Fourmiliere::getEnd_of_klan(){
    return end_of_klan;
}

void Fourmiliere::update() {
    foodReserve = foodReserve-((1+nbC+nbD+nbP)*food_rate);
    if(foodReserve<=0){
        end_of_klan = true;
    }
    for(auto entity:memberAnts){
        entity->update();
    }
    if((memberAnts[0])->getEnd_of_klan()) {
        end_of_klan = true;// if generator disapear, this too
    }
    for(unsigned int i=0;i<memberAnts.size();i++){
        if((memberAnts[i])->getSpecie()!=fourmiGeneratorCST){
            if((memberAnts[i])->getAge()>bug_life){
                memberAnts.erase(memberAnts.begin()+i);
            }
        }
    }
}

vector<vector<string>> Fourmiliere::exportToString() {
    vector<vector<string>> toExport;
    string coordX = to_string((getOccupiedSpace())->getPosition().getCoordX());
    string coordY = to_string((getOccupiedSpace())->getPosition().getCoordY());
    string height = to_string(getOccupiedSpace()->getHeight());
    string generatorX = to_string((*memberAnts[0]).getPosition().getCoordX());
    string generatorY = to_string((*memberAnts[0]).getPosition().getCoordY());
    string totalFood = to_string(foodReserve);
    string strC = to_string(nbC);
    string strD = to_string(nbD);
    string strP = to_string(nbP);

    toExport.push_back({coordX, coordY, height, generatorX, generatorY,
                        totalFood, strC, strD, strP});

    for(auto fourmi:memberAnts) {
        if(not((*fourmi).getSpecie()==fourmiGeneratorCST)) {
            vector <vector<string>> temp = (*fourmi).exportToString();
            toExport.insert(toExport.end(), temp.begin(), temp.end());
        }
    }

    return toExport;
}

void Fourmiliere::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    //int xTopRight = (*occupiedSpace).getHitboxTopRight().getCoordX();
    //int yTopRight = (*occupiedSpace).getHitboxTopRight().getCoordY();
    int xBotLeft = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int yBotLeft = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int sizeSide = (*occupiedSpace).getHeight();
    int id = getId();

    Graphic::drawPerimeter(xBotLeft, yBotLeft, id, sizeSide, false, cr);

    for(auto ant:memberAnts){
        (*ant).draw(cr);
    }





    /*
    int negBias = (-g_max*resolution/2+1);
    cr->set_source_rgb(0.8, 0.3, 0.3); // slight grey, better contrast with white item
    cr->set_line_width(5);
    cr->move_to(xTopRight*resolution+negBias, yTopRight*resolution+negBias);
    cr->line_to(xBotLeft*resolution+negBias, yTopRight*resolution+negBias);

    cr->move_to(xBotLeft*resolution+negBias, yTopRight*resolution+negBias);
    cr->line_to(xBotLeft*resolution+negBias, yBotLeft*resolution+negBias);

    cr->move_to(xBotLeft*resolution+negBias, yBotLeft*resolution+negBias);
    cr->line_to(xTopRight*resolution+negBias, yBotLeft*resolution+negBias);

    cr->move_to(xTopRight*resolution+negBias, yBotLeft*resolution+negBias);
    cr->line_to(xTopRight*resolution+negBias, yTopRight*resolution+negBias);

    cr->stroke();
    cr->restore();
    for(auto ant:memberAnts){
        (*ant).draw(cr);
    }
     */
}

void Fourmiliere::overrideAnts(vector<shared_ptr<Fourmi>> FourmiList) {
    memberAnts = FourmiList;
}

void Fourmiliere::check() {
    Fourmiliere::checkGeneratorUsingCoord();
    Fourmiliere::checkDefensorUsingCoord();
}

void Fourmiliere::checkGeneratorUsingCoord() {
    Point position;
    if((*occupiedSpace).getWidth() % 2 == 0) {
        position = Point((*occupiedSpace).getPosition().getCoordX() + 1,
                         (*occupiedSpace).getPosition().getCoordY() + 1);
    } else {
        position = (*occupiedSpace).getPosition();
    }
    int overlapSize = Squarecell::countOverlap(position,
                         (*occupiedSpace).getWidth()-2,(*occupiedSpace).getHeight()-2,
                         (*(*memberAnts[0]).getOccupiedSpace()).getPosition(),
                         (*(*memberAnts[0]).getOccupiedSpace()).getWidth(),
                         (*(*memberAnts[0]).getOccupiedSpace()).getHeight());
    if(overlapSize<(sizeG*sizeG)) {
        cout<< message::generator_not_within_home(
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordX(),
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordY(), id);
        throw (-1);
    }
}

void Fourmiliere::checkDefensorUsingCoord() {
    Point position;
    if((*occupiedSpace).getWidth() % 2 == 0) {
        position = Point((*occupiedSpace).getPosition().getCoordX() + 1,
                         (*occupiedSpace).getPosition().getCoordY() + 1);
    } else {
        position = (*occupiedSpace).getPosition();
    }
    for(auto fourmi : memberAnts) {
        if((*fourmi).getSpecie() == fourmiDefensorCST) {
            int overlapSize = Squarecell::countOverlap(position,
                                        (*occupiedSpace).getWidth()-2,
                                        (*occupiedSpace).getHeight()-2,
                                        (*(*fourmi).getOccupiedSpace()).getPosition(),
                                        (*(*fourmi).getOccupiedSpace()).getWidth(),
                                        (*(*fourmi).getOccupiedSpace()).getHeight());
            if(overlapSize<(sizeD*sizeD)) {
                cout<< message::defensor_not_within_home(
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordX(),
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordY(), id);
                throw (-1);
            }
        }
    }
}

shared_ptr<Fourmiliere> Fourmiliere::importFromExtSaveFourmilliere(
      vector<string> &inputBuffer, int index, vector<shared_ptr<Fourmi>> FourmiList,
      std::vector<std::shared_ptr<Fourmiliere>> previousAnthill) {
    if(inputBuffer.size()<9) {
        cout << "fourmilliere : number of argument mismatch" << endl;
        throw (-1);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        int size = stoi(inputBuffer[2]);
        int totalFood = stoi(inputBuffer[5]);
        int nbC = stoi(inputBuffer[6]);
        int nbD = stoi(inputBuffer[7]);
        int nbP = stoi(inputBuffer[8]);
        Squarecell::checkHitbox(Point(x,y), size, size);
        vector<Point> overlapList = Squarecell::getOverlap(
        Point(x,y),size,size,fourmilliereCST);
        int indexOther = 0;
        if(overlapList.size()>0) { // check the previous anthill for collisiom
            for(unsigned int i(0); i<previousAnthill.size(); i++) {
                int overlap = Squarecell::countOverlap(overlapList[0], overlapList[0],
                       (*previousAnthill[i]).getOccupiedSpace()->getHitboxBotLeft(),
                       (*previousAnthill[i]).getOccupiedSpace()->getHitboxTopRight());
                if(overlap) {
                    indexOther = (*previousAnthill[i]).getId();
                    break;
                }
            }
            cout << message::homes_overlap(index, indexOther);
            throw (-1);
        }
        return make_shared<Fourmiliere>(Point(x,y), size, totalFood, nbC, nbD, nbP,
                                        index, FourmiList);
    }
}