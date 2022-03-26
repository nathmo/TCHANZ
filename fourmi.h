/*!
  \file   fourmi.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/

#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#include "squarecell.h"
#include <memory>

namespace fourmi
{
    class Fourmi : public squarecell::Entity {
        private:
            int age;
        public:
            Fourmi(squarecell::Point position, int age, char type);
            virtual void update();
    };

    class Collector : public Fourmi {
        private:
            bool carryFood;
        public:
            Collector(squarecell::Point position, int age, bool carryFood);
            void update();
            static std::shared_ptr<squarecell::Entity> importFromExtSaveCollector (std::vector<std::string> &inputBuffer);
    };

    class Defensor : public Fourmi {
        public:
            Defensor(squarecell::Point position, int age);
            void update();
            static std::shared_ptr<squarecell::Entity> importFromExtSaveDefensor (std::vector<std::string> &inputBuffer);
    };

    class Predator : public Fourmi {
        public:
            Predator(squarecell::Point position, int age);
            void update();
            static std::shared_ptr<squarecell::Entity> importFromExtSavePredator (std::vector<std::string> &inputBuffer);
    };

    class Generator : public Fourmi {
        public:
            Generator(squarecell::Point position);
            void update();
            static std::shared_ptr<squarecell::Entity> importFromExtSaveGenerator (std::vector<std::string> &inputBuffer);
    };
}

#endif //TCHANZ_FOURMI_H