/*!
  \file   fourmiliere.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "fourmiliere.h"
#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Fourmiliere::Fourmiliere(Point position, int size, int totalFood,
                         int nbC, int nbD, int nbP, int id,
                         vector<shared_ptr<Fourmi>> FourmiList) :
                         Entity(position,size, size,fourmilliereCST, id, false) {
    this->nbC = nbC;
    this->nbD = nbD;
    this->nbP = nbP;
    foodReserve = totalFood;
    endOfLife = false;
    isConstrained = false;
}

int Fourmiliere::getnbC() {
    return nbC;
}

int Fourmiliere::getnbD() {
    return nbD;
}

int Fourmiliere::getnbP() {
    return nbP;
}

void Fourmiliere::update(vector<shared_ptr<Entity>> &entityList) {
    attemptExpansionAnthill();
    shared_ptr<Generator> gen = dynamic_pointer_cast<Generator> (memberAnts[0]);
    foodReserve = foodReserve + (val_food*(gen->getFood()));
    gen->removeFood(); // removed the food from the generator once added in anthill
    gen->update(entityList); // update the generator
    if(gen->getEndOfLife()) {
        endOfLife = true;
        return;
    }
    foodReserve = foodReserve - ((1+nbC+nbD+nbP)*food_rate);
    if(foodReserve <= 0) {
        endOfLife = true;
        return;
    }
    randomCreateAnts();
    for(unsigned int i=1; i < memberAnts.size(); i++) {
        memberAnts[i]->update(entityList);
    }
    removeDeadAnt(entityList);
}

void Fourmiliere::removeDeadAnt(vector<shared_ptr<Entity>> &entityList){
    int i = 0;
    while(true) {
        if((memberAnts[i])->getSpecie() != fourmiGeneratorCST) {
            if((memberAnts[i])->getEndOfLife()) {
                char kind = (memberAnts[i])->getSpecie();
                switch(kind) {
                    case fourmiCollectorCST: {
                        shared_ptr<Collector> collector =
                                dynamic_pointer_cast<Collector>(memberAnts[i]);
                        if (collector->getCarryFood()) {
                            entityList.push_back(collector->dropFood());
                        }
                        nbC--;
                        break;
                    }
                    case fourmiDefensorCST:
                        nbD--;
                        break;
                    case fourmiPredatorCST:
                        nbP--;
                        break;
                }
                memberAnts.erase(memberAnts.begin() + i);
                i--;
            }
        }
        i++;
        if(memberAnts.size() == unsigned(abs(i))) {
            break;
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
    string totalFood = to_string(int(foodReserve));
    string strC = to_string(nbC);
    string strD = to_string(nbD);
    string strP = to_string(nbP);
    toExport.push_back({coordX, coordY, height, generatorX, generatorY,
                        totalFood, strC, strD, strP});
    for(auto fourmi:memberAnts) {
        if(not((*fourmi).getSpecie() == fourmiGeneratorCST)) {
            vector<vector<string>> temp = (*fourmi).exportToString();
            toExport.insert(toExport.end(), temp.begin(), temp.end());
        }
    }
    return toExport;
}

void Fourmiliere::draw() {
    int xBotLeft = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int yBotLeft = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int sizeSide = (*occupiedSpace).getHeight();
    int id = getId();

    Squarecell::perimeter(xBotLeft, yBotLeft, sizeSide, id%6);
    for(auto ant:memberAnts) {
        (*ant).draw();
    }
}

void Fourmiliere::check() {
    Fourmiliere::checkGeneratorUsingCoord();
    Fourmiliere::checkDefensorUsingCoord();
}

void Fourmiliere::overrideAnts(vector<shared_ptr<Fourmi>> FourmiList) {
    memberAnts = FourmiList;
    if(isConstrained) {
        for(auto fourmi:memberAnts) {
            if(fourmi->getSpecie() == fourmiPredatorCST) {
                shared_ptr<Predator> predator=dynamic_pointer_cast<Predator>(fourmi);
                predator->setConstrained(isConstrained);
            }
        }
    }
}

std::vector<std::shared_ptr<Fourmi>> Fourmiliere::getAnts() {
    return memberAnts;
}

void Fourmiliere::checkGeneratorUsingCoord() {
    Point position;
    if((*occupiedSpace).getWidth()%2 == 0) {
        position = Point((*occupiedSpace).getPosition().getCoordX() + 1,
                         (*occupiedSpace).getPosition().getCoordY() + 1);
    } else {
        position = (*occupiedSpace).getPosition();
    }
    int overlapSize = Squarecell::countOverlap(position,
                         (*occupiedSpace).getWidth() - 2,
                         (*occupiedSpace).getHeight() - 2, false,
                         (*(*memberAnts[0]).getOccupiedSpace()).getPosition(),
                         (*(*memberAnts[0]).getOccupiedSpace()).getWidth(),
                         (*(*memberAnts[0]).getOccupiedSpace()).getHeight(), true);
    if(overlapSize < (sizeG*sizeG)) {
        cout << message::generator_not_within_home(
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordX(),
                (*(*memberAnts[0]).getOccupiedSpace()).getPosition().getCoordY(), id);
        throw(errorCode);
    }
}

void Fourmiliere::checkDefensorUsingCoord() {
    Point position;
    if((*occupiedSpace).getWidth()%2 == 0) {
        position = Point((*occupiedSpace).getPosition().getCoordX() + 1,
                         (*occupiedSpace).getPosition().getCoordY() + 1);
    } else {
        position = (*occupiedSpace).getPosition();
    }
    for(auto fourmi:memberAnts) {
        if((*fourmi).getSpecie() == fourmiDefensorCST) {
            int overlapSize = Squarecell::countOverlap(position,
                                (*occupiedSpace).getWidth() - 2,
                                (*occupiedSpace).getHeight() - 2, false,
                                (*(*fourmi).getOccupiedSpace()).getPosition(),
                                (*(*fourmi).getOccupiedSpace()).getWidth(),
                                (*(*fourmi).getOccupiedSpace()).getHeight(), true);
            if(overlapSize < (sizeD*sizeD)) {
                cout << message::defensor_not_within_home(
                       (*(*fourmi).getOccupiedSpace()).getPosition().getCoordX(),
                       (*(*fourmi).getOccupiedSpace()).getPosition().getCoordY(), id);
                throw (errorCode);
            }
        }
    }
}

void Fourmiliere::randomCreateAnts() {
    if(biasedCoinFlip(float(min(birth_rate*foodReserve, 1.0)))) {
        shared_ptr<Fourmi> ant;
        int antTypeToGenerate = Fourmiliere::getAntTypeToGenerate();
        // remove the border from allowed zone
        Point cornerBL = Point((*occupiedSpace).getHitboxBotLeft().getCoordX() + 1,
                               (*occupiedSpace).getHitboxBotLeft().getCoordY() + 1);
        Point cornerTR = Point((*occupiedSpace).getHitboxTopRight().getCoordX() - 1,
                               (*occupiedSpace).getHitboxTopRight().getCoordY() - 1);
        Point position;
        vector<Point> spawn=Squarecell::findFreeInArea(cornerBL, cornerTR,
                                                       sizeC, sizeC, anyCST);
        if(spawn.size() > 0) {
            position = spawn[Entity::randInt(0, spawn.size()-1)];
            switch(antTypeToGenerate) {
                case 0  : { //Collector
                    ant = make_shared<Collector> (position, id, 0, false);
                    nbC++;
                    break;
                }
                case 1  : {//Defensor
                    ant = make_shared<Defensor> (position, id, 0);
                    nbD++;
                    break;
                }
                case 2  : {//Predator
                    ant = make_shared<Predator> (position, id, 0);
                    nbP++;
                    break;
                }
            }
            memberAnts.push_back(ant);
        }
    }
}

int Fourmiliere::getAntTypeToGenerate() {
    int antTypeToGenerate = 0;
    if(isConstrained) {
        if((memberAnts.size()-1)*prop_constrained_collector >= nbC) {
            antTypeToGenerate = 0;
        } else if((memberAnts.size()-1)*prop_constrained_defensor >= nbD) {
            antTypeToGenerate = 1;
        } else {
            antTypeToGenerate = 2;
        }
    } else {
        if((memberAnts.size()-1)*prop_free_collector >= nbC) {
            antTypeToGenerate = 0;
        } else if((memberAnts.size()-1)*prop_free_defensor >= nbD) {
            antTypeToGenerate = 1;
        } else {
            antTypeToGenerate = 2;
        }
    }
    return antTypeToGenerate;
}

void Fourmiliere::attemptExpansionAnthill() {
    int sizeF = floor(sqrt(4*(sizeG*sizeG  + sizeC*sizeC*nbC + sizeD*sizeD*nbD
                              + sizeP*sizeP*nbP)));
    int delta = sizeF + 1 - (*occupiedSpace).getWidth();
    Point originLL = (*occupiedSpace).getHitboxBotLeft();
    Point originUL = Point((*occupiedSpace).getHitboxBotLeft().getCoordX(),
                           (*occupiedSpace).getHitboxBotLeft().getCoordY()-delta);
    Point originUR = Point((*occupiedSpace).getHitboxBotLeft().getCoordX()-delta,
                           (*occupiedSpace).getHitboxBotLeft().getCoordY()-delta);
    Point originLR = Point((*occupiedSpace).getHitboxBotLeft().getCoordX()-delta,
                           (*occupiedSpace).getHitboxBotLeft().getCoordY());
    int anthillArea = ((*occupiedSpace).getWidth()*(*occupiedSpace).getHeight());
    vector<Point> pointToTest = {originLL, originUL, originUR, originLR};
    for(auto point:pointToTest) {
        if(Squarecell::ensureFitInGrid(point, sizeF+2, sizeF+2, false)) {
            if(Squarecell::countOverlap(point, sizeF+2, sizeF+2,fourmilliereCST,false)
                                                                     <= anthillArea) {
                (*occupiedSpace).setPosition(point);
                (*occupiedSpace).setSize(sizeF+2, sizeF+2);
                isConstrained = false;
                return;
            }
        }
    }
    isConstrained = true;
    for(auto fourmi:memberAnts) {
        if(fourmi->getSpecie() == fourmiPredatorCST) {
            shared_ptr<Predator> predator = dynamic_pointer_cast<Predator> (fourmi);
            predator->setConstrained(isConstrained);
        }
    }
}

double Fourmiliere::getFood() {
    shared_ptr<Generator> gen = dynamic_pointer_cast<Generator> (memberAnts[0]);
    return foodReserve + (val_food*(gen->getFood()));
}

shared_ptr<Fourmiliere> Fourmiliere::importFromExtSaveFourmilliere(
        vector<string> &inputBuffer, int index, vector<shared_ptr<Fourmi>> FourmiList,
        std::vector<std::shared_ptr<Fourmiliere>> previousAnthill) {
    if(inputBuffer.size() < 9) {
        cout << "fourmilliere : number of argument mismatch" << endl;
        throw (errorCode);
    } else {
        long int x = stoi(inputBuffer[0]);
        long int y = stoi(inputBuffer[1]);
        int size = stoi(inputBuffer[2]);
        int totalFood = stoi(inputBuffer[5]);
        int nbC = stoi(inputBuffer[6]);
        int nbD = stoi(inputBuffer[7]);
        int nbP = stoi(inputBuffer[8]);
        Squarecell::checkHitbox(Point(x, y), size, size, false);
        vector<Point> overlapList = Squarecell::getOverlap(Point::checkPoint(x, y),
                                                  size, size, fourmilliereCST, false);
        int indexOther = 0;
        if(overlapList.size() > 0) { // check the previous anthill for collisiom
            for(unsigned int i(0); i < previousAnthill.size(); i++) {
                int overlap = Squarecell::countOverlap(overlapList[0], overlapList[0],
                       (*previousAnthill[i]).getOccupiedSpace()->getHitboxBotLeft(),
                       (*previousAnthill[i]).getOccupiedSpace()->getHitboxTopRight());
                if(overlap) {
                    indexOther = (*previousAnthill[i]).getId();
                    break;
                }
            }
            cout << message::homes_overlap(index, indexOther);
            throw(errorCode);
        }
        return make_shared<Fourmiliere> (Point(x, y), size, totalFood, nbC, nbD, nbP,
                                        index, FourmiList);
    }
}