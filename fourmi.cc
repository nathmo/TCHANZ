/*!
  \file   fourmi.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "fourmi".
*/

#include "fourmi.h"
#include "squarecell.h"
#include "constantes.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

fourmi::Fourmi::Fourmi(squarecell::Point position, int age, char type)  :
squarecell::Entity(position, squarecell::Point(1,1), type)
{
    this->age = age;
}
void fourmi::Fourmi::update()
{
    cout << "error, trying to update a generic fourmi object" << endl;
}

fourmi::Collector::Collector(squarecell::Point position, int age, bool carryFood) :
        fourmi::Fourmi(position, age, fourmiCollectorCST)
{
    this->carryFood = carryFood;
}
void fourmi::Collector::update()
{

}
shared_ptr<squarecell::Entity> fourmi::Collector::importFromExtSaveCollector (vector<string>inputBuffer) {
    if(!(inputBuffer.size()<=4)) {
        cout << "Collector : number of argument mismatch" << endl;
        exit(0);
    }else{
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    bool condition_food = false;
    if("true" == inputBuffer[3]) {
    condition_food = true;
    }
    return make_shared<fourmi::Collector>(squarecell::Point(x,y),age,condition_food);
    }
}

fourmi::Defensor::Defensor(squarecell::Point position, int age) :
        fourmi::Fourmi(position, age, fourmiDefensorCST) {}
void fourmi::Defensor::update()
{

}
shared_ptr<squarecell::Entity> fourmi::Defensor::importFromExtSaveDefensor (vector<string>inputBuffer) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Defensor : number of argument mismatch" << endl;
        exit(0);
    }else{
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    return make_shared<fourmi::Defensor>(squarecell::Point(x,y),age);
    }
}

fourmi::Predator::Predator(squarecell::Point position, int age) :
        fourmi::Fourmi(position, age, fourmiPredatorCST) {}
void fourmi::Predator::update()
{

}
shared_ptr<squarecell::Entity> fourmi::Predator::importFromExtSavePredator (vector<string>inputBuffer) {
    if(!(inputBuffer.size()<=3)) {
        cout << "Predator : number of argument mismatch" << endl;
        exit(0);
    }else{
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    int age = stoi(inputBuffer[2]);
    return make_shared<fourmi::Predator>(squarecell::Point(x,y),age);
    }
}
fourmi::Generator::Generator(squarecell::Point position) :
        fourmi::Fourmi(position,0 , fourmiGeneratorCST) {}
void fourmi::Generator::update()
{

}
shared_ptr<squarecell::Entity> fourmi::Generator::importFromExtSaveGenerator (vector<string>inputBuffer){
    int x = stoi(inputBuffer[0]);
    int y = stoi(inputBuffer[1]);
    return make_shared<fourmi::Generator>(squarecell::Point(x,y));
}

