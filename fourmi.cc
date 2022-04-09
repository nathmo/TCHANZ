/*!
  \file   fourmi.cc
  \author Nathann Morand (30%) et Felipe Ramirez (70%)
  \date   MARS 2022
  \brief  implémentation du module "fourmi".
*/
#include <iostream>
#include <string>
#include <memory>
#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>
#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"

using namespace std;

Fourmi::Fourmi(Point position, int age, char type, int id, int size)  :
        Entity(position, size, size, type, id) {
    this->age = age;
    end_of_klan = false;
}

bool Fourmi::getEnd_of_klan(){
    return end_of_klan;
}

int Fourmi::getAge(){
    return age;
}

void Fourmi::update() {
    cout << "error, trying to update a generic fourmi object" << endl;
    exit(EXIT_FAILURE);
}

vector<vector<string>> Fourmi::exportToString(){
    vector<vector<string>> toExport;
    cout << "ERROR : exporting a generic ant type" << endl;
    exit(EXIT_FAILURE);
    return toExport;
}

void Fourmi::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    cout << "trying to draw a generic fourmi" << endl;
    exit(EXIT_FAILURE);
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
        Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update() {
    age++;
}

vector<vector<string>> Collector::exportToString() {
    vector<vector<string>> vecVecStringCollector;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string carryFoodString = "False";
    if(carryFood) {
        carryFoodString = "True";
    }
    string ageString = to_string(age);
    vecVecStringCollector.push_back({x,y,ageString,carryFoodString});
    return vecVecStringCollector;
}

shared_ptr<Fourmi> Collector::importFromExtSaveCollector(vector<string> &inputBuffer,
                                                         int index) {
    if(!(inputBuffer.size()<=4)) {
        cout << "Collector : number of argument mismatch" << endl;
        throw (-1);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    bool conditionFood = false;
    if("true" == inputBuffer[3]) {
        conditionFood = true;
    }
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeC, sizeC,
                                                       anyCST);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Collector>(Point(x,y),index ,age,conditionFood);
    }
}

void Collector::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    int negBias = (-g_max*resolution/2+1);
    // draw square
    cr->set_source_rgb(0.8, 0.2, 0.8);
    cr->set_line_width((resolution));
    cr->move_to((x)*resolution+negBias+1, (y+0.5)*resolution+negBias+1);
    cr->line_to((x+1)*resolution+negBias,(y+0.5)*resolution+negBias);
    cr->stroke();
}

Defensor::Defensor(Point position, int id, int age) :
        Fourmi(position, age,fourmiDefensorCST,id, sizeD)  {
}

void Defensor::update() {
    age++;
}

vector<vector<string>> Defensor::exportToString() {
    vector<vector<string>> vecVecStringDefensor;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringDefensor.push_back({x,y,ageString});
    return vecVecStringDefensor;
}

shared_ptr<Fourmi> Defensor::importFromExtSaveDefensor(vector<string> &inputBuffer,
                                                       int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        throw (-1);
    } else {
    long int x = stoi(inputBuffer[0]);
    long int y = stoi(inputBuffer[1]);
    long int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeD, sizeD,
                                                       anyCST);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::defensor_overlap(x,y, overlapList[0].getCoordX(),
                                         overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Defensor>(Point(x,y), index,age);
    }
}

void Defensor::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    int negBias = (-g_max*resolution/2+1);
    // draw square
    cr->set_source_rgb(0, 0.2, 1);
    cr->set_line_width((resolution));
    cr->move_to((x)*resolution+negBias+1, (y+0.5)*resolution+negBias+1);
    cr->line_to((x+1)*resolution+negBias,(y+0.5)*resolution+negBias);
    cr->stroke();
}

Predator::Predator(Point position, int id, int age) :
        Fourmi(position, age, fourmiPredatorCST, id, sizeP) {
}

void Predator::update() {
    age++;
}

vector<vector<string>> Predator::exportToString() {
    vector<vector<string>> vecVecStringPredator;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringPredator.push_back({x,y,ageString});
    return vecVecStringPredator;
}

shared_ptr<Fourmi> Predator::importFromExtSavePredator(vector<string> &inputBuffer,
                                                       int index) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Predator : number of argument mismatch" << endl;
        throw (-1);
    } else {
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeP, sizeP,
                                                       anyCST);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::predator_overlap(x,y);
        throw (-1);
    }
    return make_shared<Predator>(Point(x,y),index,age);
    }
}

void Predator::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    int negBias = (-g_max*resolution/2+1);
    // draw square
    cr->set_source_rgb(1, 0, 0.2);
    cr->set_line_width((resolution));
    cr->move_to((x)*resolution+negBias+1, (y+0.5)*resolution+negBias+1);
    cr->line_to((x+1)*resolution+negBias,(y+0.5)*resolution+negBias);
    cr->stroke();
}

Generator::Generator(Point position, int id) :
        Fourmi(position,0 , fourmiGeneratorCST, id, sizeG) {
}

void Generator::update() {
    age++;
}

vector<vector<string>> Generator::exportToString() {
    vector<vector<string>> vecVecStringGenerator;
    Point position = (*occupiedSpace).getPosition();
    string x = to_string(position.getCoordX());
    string y = to_string(position.getCoordY());
    string ageString = to_string(age);
    vecVecStringGenerator.push_back({x,y,ageString});
    return vecVecStringGenerator;
}

shared_ptr<Fourmi> Generator::importFromExtSaveGenerator(vector<string> &inputBuffer,
                                                         int index) {
    int x = stoi(inputBuffer[3]);
    int y = stoi(inputBuffer[4]);
    vector<Point> overlapList = Squarecell::getOverlap(Point(x,y), sizeG, sizeG,
                                                       anyCST);
    if(overlapList.size()>0) { // ensure the ant does not collide with something else
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Generator>(Point(x,y), index);
}

void Generator::draw(const Cairo::RefPtr<Cairo::Context>& cr){
    int x = (*occupiedSpace).getPosition().getCoordX();
    int y = (*occupiedSpace).getPosition().getCoordY();
    int negBias = (-g_max*resolution/2+1);
    // draw square
    cr->set_source_rgb(0, 0.5, 0.5);
    cr->set_line_width((resolution));
    cr->move_to((x)*resolution+negBias+1, (y+0.5)*resolution+negBias+1);
    cr->line_to((x+1)*resolution+negBias,(y+0.5)*resolution+negBias);
    cr->stroke();
}