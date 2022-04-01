/*!
  \file   fourmi.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "fourmi".
*/

#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

fourmi::Fourmi::Fourmi(squarecell::Point position, int age, char type, int id, int size)  :
        entity::Entity(position, size, size, type, id) {
    this->age = age;
}

void fourmi::Fourmi::update() {
    cout << "error, trying to update a generic fourmi object" << endl;
}

fourmi::Collector::Collector(squarecell::Point position, int id, int age, bool carryFood ) :
        fourmi::Fourmi(position, age,fourmiCollectorCST,id,fourmi::sizeC) {
    this->carryFood = carryFood;
}

void fourmi::Collector::update() {

}

shared_ptr<fourmi::Fourmi> fourmi::Collector::importFromExtSaveCollector(vector<string> &inputBuffer,
                                                                          int index) {
    if(!(inputBuffer.size()<=4)) {
        cout << "Collector : number of argument mismatch" << endl;
        exit(0);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    bool condition_food = false;
    if("true" == inputBuffer[3]) {
        condition_food = true;
    }
    vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap(squarecell::Point(x,y),
                                                                               fourmi::sizeC,
                                                                               fourmi::sizeC, anyCST);
    if(overlapList.size()>0) {
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<fourmi::Collector>(squarecell::Point(x,y),index ,age,condition_food);
    }
}

fourmi::Defensor::Defensor(squarecell::Point position, int id, int age) :
        fourmi::Fourmi(position, age,fourmiDefensorCST,id, fourmi::sizeD)  {
}

void fourmi::Defensor::update() {

}

shared_ptr<fourmi::Fourmi> fourmi::Defensor::importFromExtSaveDefensor(vector<string> &inputBuffer,
                                                                        int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        exit(0);
    }else{
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap(squarecell::Point(x,y),
                                                                               fourmi::sizeD,
                                                                               fourmi::sizeD, anyCST);
    if(overlapList.size()>0) {
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<fourmi::Defensor>(squarecell::Point(x,y), index,age);
    }
}

fourmi::Predator::Predator(squarecell::Point position, int id, int age) :
        fourmi::Fourmi(position, age, fourmiPredatorCST, id, sizeP) {
}

void fourmi::Predator::update() {

}

shared_ptr<fourmi::Fourmi> fourmi::Predator::importFromExtSavePredator(vector<string> &inputBuffer,
                                                                        int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Predator : number of argument mismatch" << endl;
        exit(0);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap(squarecell::Point(x,y), fourmi::sizeP, fourmi::sizeP, anyCST);
    if(overlapList.size()>0) {
        cout<< message::predator_overlap(x,y);
        exit(EXIT_FAILURE);
    }
    return make_shared<fourmi::Predator>(squarecell::Point(x,y),index,age);
    }
}

fourmi::Generator::Generator(squarecell::Point position, int id) :
        fourmi::Fourmi(position,0 , fourmiGeneratorCST, id, sizeG) {
}

void fourmi::Generator::update() {

}

shared_ptr<fourmi::Fourmi> fourmi::Generator::importFromExtSaveGenerator(vector<string> &inputBuffer, int index) {
    int x = stoi(inputBuffer[3]);
    int y = stoi(inputBuffer[4]);
    vector<squarecell::Point> overlapList = squarecell::Squarecell::getOverlap(squarecell::Point(x,y),
                                                                               fourmi::sizeG,
                                                                               fourmi::sizeG, anyCST);
    if(overlapList.size()>0) {
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<fourmi::Generator>(squarecell::Point(x,y), index);
}

