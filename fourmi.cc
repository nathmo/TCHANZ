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

Fourmi::Fourmi(Point position, int age, char type, int id, int size)  :
        Entity(position, size, size, type, id) {
    this->age = age;
}

void Fourmi::update() {
    cout << "error, trying to update a generic fourmi object" << endl;
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
        Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update() {

}

shared_ptr<Fourmi> Collector::importFromExtSaveCollector(vector<string> &inputBuffer,
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
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y),
                                                                               sizeC,
                                                                               sizeC, anyCST);
    if(overlapList.size()>0) {
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<Collector>(Point(x,y),index ,age,condition_food);
    }
}

Defensor::Defensor(Point position, int id, int age) :
        Fourmi(position, age,fourmiDefensorCST,id, sizeD)  {
}

void Defensor::update() {

}

shared_ptr<Fourmi> Defensor::importFromExtSaveDefensor(vector<string> &inputBuffer,
                                                                        int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        exit(0);
    }else{
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y),
                                                                               sizeD,
                                                                               sizeD, anyCST);
    if(overlapList.size()>0) {
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<Defensor>(Point(x,y), index,age);
    }
}

Predator::Predator(Point position, int id, int age) :
        Fourmi(position, age, fourmiPredatorCST, id, sizeP) {
}

void Predator::update() {

}

shared_ptr<Fourmi> Predator::importFromExtSavePredator(vector<string> &inputBuffer,
                                                                        int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Predator : number of argument mismatch" << endl;
        exit(0);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeP, sizeP, anyCST);
    if(overlapList.size()>0) {
        cout<< message::predator_overlap(x,y);
        exit(EXIT_FAILURE);
    }
    return make_shared<Predator>(Point(x,y),index,age);
    }
}

Generator::Generator(Point position, int id) :
        Fourmi(position,0 , fourmiGeneratorCST, id, sizeG) {
}

void Generator::update() {

}

shared_ptr<Fourmi> Generator::importFromExtSaveGenerator(vector<string> &inputBuffer, int index) {
    int x = stoi(inputBuffer[3]);
    int y = stoi(inputBuffer[4]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y),
                                                                               sizeG,
                                                                               sizeG, anyCST);
    if(overlapList.size()>0) {
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(), overlapList[0].getCoordY());
        exit(EXIT_FAILURE);
    }
    return make_shared<Generator>(Point(x,y), index);
}

