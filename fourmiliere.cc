/*!
  \file   fourmiliere.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/


#include "fourmiliere.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"
#include <iostream>
#include <memory>
using namespace std;

fourmiliere::Fourmiliere::Fourmiliere(squarecell::Point position,int size,int total_food,int nbC,int nbD,int nbP,int id, vector<shared_ptr<fourmi::Fourmi>> FourmiList) :
        entity::Entity(position, size, size, fourmilliereCST, id) {
    foodReserve = total_food;
    this->nbC=nbC;
    this->nbD=nbD;
    this->nbP=nbP;
    memberAnts = FourmiList;
}

void fourmiliere::Fourmiliere::update() {

}

void fourmiliere::Fourmiliere::overrideAnts(vector<shared_ptr<fourmi::Fourmi>> FourmiList) {
    memberAnts = FourmiList;
    vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap((*occupiedSpace).getPosition(), (*occupiedSpace).getWidth(), (*occupiedSpace).getHeight(), fourmiGeneratorCST);
    if(overlapList.size()<(sizeG*sizeG)) {
        cout<< message::generator_not_within_home((*occupiedSpace).getPosition().getCoordX(),(*occupiedSpace).getPosition().getCoordY(),id);
        exit(EXIT_FAILURE);
    }
    for(auto fourmi : memberAnts) {
        if ((*fourmi).getSpecie() == fourmiDefensorCST)
        {
            squarecell::Point position;
            if ((*occupiedSpace).getWidth() % 2 == 0) {
                position = squarecell::Point(
                        (*occupiedSpace).getPosition().getCoordX() + 1,
                        (*occupiedSpace).getPosition().getCoordY() + 1);
            } else {
                position = (*occupiedSpace).getPosition();
            }
            overlapList = squarecell::Squarecell::getOverlap(position,
            ((*occupiedSpace).getWidth()-2),((*occupiedSpace).getHeight()-2),
                                                             fourmiDefensorCST);
            unsigned int expectedNumberOfCoveredTile = ((sizeD * sizeD) * nbD);
            if (overlapList.size() < expectedNumberOfCoveredTile) { // ici la bordure ne doit pas overlappé non plus
                cout << message::defensor_not_within_home(
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordX(),
                        (*(*fourmi).getOccupiedSpace()).getPosition().getCoordY(), id);
                exit(EXIT_FAILURE);
            }
        }
    }
    //squarecell::Squarecell::displayRawBoolGrid();
}

shared_ptr<fourmiliere::Fourmiliere> fourmiliere::Fourmiliere::importFromExtSaveFourmilliere(vector<string> &inputBuffer, int index,
                                                                                vector<shared_ptr<fourmi::Fourmi>> FourmiList) {
    if(inputBuffer.size()<9) {
        cout << "fourmilliere : number of argument mismatch" << endl;
        exit(EXIT_FAILURE);
    } else {
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        int size = stoi(inputBuffer[2]);
        int total_food = stoi(inputBuffer[5]);
        int nbC = stoi(inputBuffer[6]);
        int nbD = stoi(inputBuffer[7]);
        int nbP = stoi(inputBuffer[8]);
        vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap(
        squarecell::Point(x,y),size,size,fourmilliereCST);
        if(overlapList.size()>0) {
            //int indexOtherAnthill = entity::Entity::findIdByOccupingPoint(overlapList, std::vector<std::shared_ptr<entity::Entity>> allEntitys);
            int indexOtherAnthill = 0;
            cout << message::homes_overlap(index, indexOtherAnthill); // SET INDEX HERE TODO INDEX FUNCTION
            exit(EXIT_FAILURE);
        }
        return make_shared<fourmiliere::Fourmiliere>(squarecell::Point(x,y), size,total_food,nbC,nbD,nbP,index, FourmiList);
    }
}