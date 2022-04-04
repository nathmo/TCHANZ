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
    for(auto entity:memberAnts){
        entity->update();
    }
}

vector<vector<string>> Fourmiliere::export(){
    vector<vector<string>> toExport;
    cout << "exporting an anthill" << endl;
    return toExport;
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
      vector<string> &inputBuffer, int index, vector<shared_ptr<Fourmi>> FourmiList,
      std::vector<std::shared_ptr<Fourmiliere>> previousAnthill) {
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
            exit(EXIT_FAILURE);
        }
        return make_shared<Fourmiliere>(Point(x,y), size, totalFood, nbC, nbD, nbP,
                                        index, FourmiList);
    }
}

int Fourmiliere::getFoodReserve() {
    return foodReserve;
}

int Fourmiliere::getNbC() {
    return nbC;
}

int Fourmiliere::getNbD() {
    return nbD;
}

int Fourmiliere::getNbP() {
    return nbP;
}

vector<vector<string>> Fourmiliere::anthillVecToExport(vector<string> &listOfEntity,
                                                       int quantityFood){

     //boucle while ou for pour faire chaque fourmiliere qui est presente dans la liste

        string coordX = to_string(((*listOfEntity[quantityFood +1])->getOccupiedSpace)->getPosition).getCoordX;
        string coordY = to_string(((*listOfEntity[quantityFood +1])->getOccupiedSpace)->getPosition).getCoordY;
        string height = to_string((*listOfEntity[quantityFood + 1])->getOccupiedSpace)->getHeight;
        //string width = to_string((*listOfEntity[quantityFood+1])->getOccupiedSpace)->getWidth; // vu qu on part du principe fourmiliere forcement carre
        //position generator
        string totalFood = to_string((*listOfEntity[quantityFood + 1]).getFoodReserve);
        string nbC = to_string((*listOfEntity[quantityFood + 1]).getNbC);
        string nbD = to_string((*listOfEntity[quantityFood + 1]).getNbD);
        string nbP = to_string((*listOfEntity[quantityFood + 1]).getNbP);
        vector<vector<string>> vecVecStringAnthillAnt.push_back({coordX, coordY, height, height, GENERATOR, totalFood, nbC, nbD, nbP}); //manque generator


        //appeler les differentes fonction des fourmis pour les insert ici

    return vecVecStringAnthillAnt;
}

