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

fourmi::Defensor::Defensor(squarecell::Point position, int age) :
        fourmi::Fourmi(position, age, fourmiDefensorCST) {}
void fourmi::Defensor::update()
{

}
fourmi::Predator::Predator(squarecell::Point position, int age) :
        fourmi::Fourmi(position, age, fourmiPredatorCST) {}
void fourmi::Predator::update()
{

}

fourmi::Generator::Generator(squarecell::Point position) :
        fourmi::Fourmi(position,0 , fourmiGeneratorCST) {}
void fourmi::Generator::update()
{

}