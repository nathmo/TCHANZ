/*!
  \file   fourmi.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/

#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#include "squarecell.h"

namespace fourmi
{

class Fourmi : public squarecell::Entity
    {
    private:
        int age;
    public:
        Fourmi(squarecell::Point position, int age, char type);
        virtual void update();
    };
    class Collector : public Fourmi
    {
    private:
        bool carryFood;
    public:
        Collector(squarecell::Point position, int age, bool carryFood);
        void update();
        shared_ptr<squarecell::Entity> importFromExtSaveCollector const(std::vector<std::string>inputBuffer);
    };
    class Defensor : public Fourmi
    {
    public:
        Defensor(squarecell::Point position, int age);
        void update();
        shared_ptr<squarecell::Entity> importFromExtSaveDefensor const(std::vector<std::string>inputBuffer);
    };
    class Predator : public Fourmi
    {
    public:
        Predator(squarecell::Point position, int age);
        void update();
        shared_ptr<squarecell::Entity> importFromExtSavePredator const(std::vector<std::string>inputBuffer);
    };
    class Generator : public Fourmi
    {
    public:
        Generator(squarecell::Point position);
        void update();
        shared_ptr<squarecell::Entity> importFromExtSaveGenerator const(std::vector<std::string>inputBuffer);
    };
}

#endif //TCHANZ_FOURMI_H