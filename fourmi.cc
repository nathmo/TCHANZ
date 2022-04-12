/*!
  \file   fourmi.cc
  \author Nathann Morand (30%) et Felipe Ramirez (70%)
  \date   MARS 2022
  \brief  implémentation du module "fourmi".
*/
#include <iostream>
#include <string>
#include <memory>
#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include "message.h"
#include "graphic.h"

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

vector<vector<double>> Fourmi::draw(){
    cout << "trying to draw a generic fourmi" << endl;
    exit(EXIT_FAILURE);
    return {{}};
}

Collector::Collector(Point position, int id, int age, bool carryFood ) :
        Fourmi(position, age,fourmiCollectorCST,id,sizeC) {
    this->carryFood = carryFood;
}

void Collector::update() {
/*
    vector<Point> listSpecie = Entity::findSpecie(nourritureCST);
    vector<Point> listSpecieTrie;

    int xOrigin = getPosition().getCoordX();
    int yOrigin = getPosition().getCoordY();

    bool case = (xOrigin+yOrigin)%2; //savoir si case noir ou blanche

    //classer les food qui sont sur meme couleur case
    for(auto entity : listSpecie) {
        int x = entity.getCoordX();
        int y = entity.getCoordY();
        if((x+y)%2 == case) {
            listSpecieTrie.push_back(entity);
        }
    }
    age++;
    */
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
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::collector_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Collector>(Point(x,y), index , age, conditionFood);
    }
}

vector<vector<double>> Collector::draw() {
    vector<vector<double>> commandList;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = 3;
    int id = getId()%6;
    int lightColor = id+6;
    int colorCode = id; //on commence en bas a gauche donc foncé au debut

   // int xBotLeft, int yBotLeft,  int sizeSide, int colorCode

    for (int i(0); i < side; i++) {
        for (int j(0); j < side; j++) {
            vector<vector<double>> cmd = Squarecell::square(x + j, y + i, colorCode);
            commandList.insert(commandList.end(), cmd.begin(), cmd.end());
            if (colorCode == id) {
                colorCode = lightColor;
            } else {
                colorCode = id;
            }
        }
    }
    return commandList;
}
/*
    for(int i(0); i < side; i++) { //depuis bas jusqu'en haut on dessine case par case
        for(int j(0); j < side; j++) {
            //(x+i, y+j, id, lightColor, squareType)
            Graphic::drawSquare(x+i, y+j, id, lightColor, cr);
            if(lightColor == true) {
                lightColor = false;
            } else {
                lightColor = true;
            }
        }
    }
    Graphic::drawSquare(originX, originY, id, false, cr); //mettre le centre foncé
}
*/

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

vector<vector<double>> Defensor::draw() {
    vector <vector<double>> list;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = 3;
    int lightColor = 0;
    int id = getId();
/*
    for (int i(0); i < side; i++) {
        for (int j(0); j < side; i++) {
            list.push_back({x + j, y + i, id, lightColor, 0}); //le centre ca joue pas vu que ca alterne pas bien
            if (lightColor == 1) {
                lightColor = 0;
            } else {
                lightColor = 1;
            }
        }
    }
    list[4][3] = 0; //mettre le centre a foncé
*/
    return list;
}

/*
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int originX = (*occupiedSpace).getPosition().getCoordX();
    int originY = (*occupiedSpace).getPosition().getCoordY();
    int side = (*occupiedSpace).getHeight();
    bool lightColor = true;
    int id = getId();

    for(int i(0); i < side; i++) { //depuis bas jusqu'en haut on dessine case par case
        for(int j(0); j < side; j++) {
            Graphic::drawSquare(x+i, y+j, id, lightColor, cr);

            if(lightColor == true) {
                lightColor = false;
            } else {
                lightColor = true;
            }
        }
    }
    Graphic::drawSquare(originX, originY, id, false, cr); //mettre le centre foncé
}
*/


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

vector<vector<double>> Predator::draw() {
    vector <vector<double>> list;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int id = getId();
/*
    list.push_back({x, y, id, 0, 0}); //le centre ca joue pas vu que ca alterne pas bien
*/
    return list;;

}
/*
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = (*occupiedSpace).getHeight();
    int id = getId();

    for(int i(0); i < side; i++) { //depuis en bas jusqu a en haut on dessine case par case
        for(int j(0); j < side; j++) {
            Graphic::drawSquare(x+i, y+j, id, false, cr);
        }
    }
}
*/

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
    if(overlapList.size()>0) { //ensure the ant does not collide with something else
        cout<< message::generator_overlap(x,y, overlapList[0].getCoordX(),
                                          overlapList[0].getCoordY());
        throw (-1);
    }
    return make_shared<Generator>(Point(x,y), index);
}

vector<vector<double>> Generator::draw() {
    vector <vector<double>> list;
    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = (*occupiedSpace).getHeight();
    int id = getId();
    /*
    for (int i(0); i < side; i++) {
        for (int j(0); j < side; i++) {
            list.push_back({x + j, y + i, id, side, 0});
        }
    }
     */
    return list;
}

   /*



    int x = (*occupiedSpace).getHitboxBotLeft().getCoordX();//point bas, plus simple
    int y = (*occupiedSpace).getHitboxBotLeft().getCoordY();
    int side = (*occupiedSpace).getHeight();
    int id = getId();

    for(int i(0); i < side; i++) {//depuis bas jusqu'en haut on dessine case par case
        for(int j(0); j < side; j++) {
            (x+i, y+j, id, side, 1);
        }
    }
}
    */