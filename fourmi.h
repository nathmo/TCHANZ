/*!
  \file   fourmi.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/

#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#import "squarecell.h"

namespace fourmi
{

class Fourmi : public squarecell::Entity
    {
    private:
        int age;
    public:
        Fourmi(squarecell::Point position, int age);
    };
    class Collector : public Fourmi
    {
    private:
        bool carryFood;
    public:
        Collector(squarecell::Point position, int age, bool carryFood);
        update();
    };
    class Defensor : public Fourmi
    {
    public:
        Defensor(squarecell::Point position, int age);
        update();
    };
    class Predator : public Fourmi
    {
    public:
        Predator(squarecell::Point position, int age);
        update();
    };
    class Generator : public Fourmi
    {
    public:
        Generator(squarecell::Point position);
        update();
    };
}

#endif //TCHANZ_FOURMI_H