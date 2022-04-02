/*!
  \file   fourmiliere.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/
#include <iostream>
#include <memory>
#include "fourmiliere.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

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
}

void Fourmiliere::update() {
    cout << "updating the Fourmiliere with id "+to_string(id) << endl;
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
        position = Point(
                (*occupiedSpace).getPosition().getCoordX() + 1,
                (*occupiedSpace).getPosition().getCoordY() + 1);
    } else {
        position = (*occupiedSpace).getPosition();
    }
    int overlapSize = Squarecell::countOverlap(
            position, (*occupiedSpace).getWidth()-2,(*occupiedSpace).getHeight()-2,
            (*(*memberAnts[0]).getOccupiedSpace()).getPosition(),
            (*(*memberAnts[0]).getOccupiedSpace()).getWidth(),
            (*(*memberAnts[0]).getOccupiedSpace()).getHeight());
    if(overlapSize<(sizeG*sizeG))
    {
        cout<< message::generator_not_within_home(
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordX(),
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordY(), id);
        exit(EXIT_FAILURE);
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
        if ((*fourmi).getSpecie() == fourmiDefensorCST) {
            int overlapSize = Squarecell::countOverlap(position,
                                        (*occupiedSpace).getWidth()-2,
                                        (*occupiedSpace).getHeight()-2,
                                        (*(*fourmi).getOccupiedSpace()).getPosition(),
                                        (*(*fourmi).getOccupiedSpace()).getWidth(),
                                        (*(*fourmi).getOccupiedSpace()).getHeight());
            if(overlapSize<(sizeD*sizeD))
            {
                cout<< message::defensor_not_within_home(
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordX(),
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordY(), id);
                exit(EXIT_FAILURE);
            }
        }
    }
}

shared_ptr<Fourmiliere> Fourmiliere::importFromExtSaveFourmilliere(
      vector<string> &inputBuffer, int index, vector<shared_ptr<Fourmi>> FourmiList) {
    if(inputBuffer.size()<9) {
        cout << "fourmilliere : number of argument mismatch" << endl;
        exit(EXIT_FAILURE);
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
        if(overlapList.size()>0) {
            //int indexOtherAnthill = Entity::findIdByOccupingPoint(overlapList,
            //                       std::vector<std::shared_ptr<Entity>> allEntitys);
            int indexOtherAnthill = 0;
            cout << message::homes_overlap(index, indexOtherAnthill); // SET INDEX HERE TODO INDEX FUNCTION
            exit(EXIT_FAILURE);
        }
        return make_shared<Fourmiliere>(Point(x,y), size, totalFood, nbC, nbD, nbP,
                                        index, FourmiList);
    }
}