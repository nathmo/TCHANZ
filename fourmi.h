/*!
  \file   fourmi.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmi".
*/

#ifndef TCHANZ_FOURMI_H
#define TCHANZ_FOURMI_H

#include "squarecell.h"
#include "entity.h"
#include <memory>

namespace fourmi {
    constexpr short unsigned sizeG(5) ;
    constexpr short unsigned sizeC(3) ;
    constexpr short unsigned sizeD(3) ;
    constexpr short unsigned sizeP(1) ;
    constexpr short unsigned bug_life(300) ;
    class Fourmi : public entity::Entity {
        protected:
            int age;
        public:
            Fourmi(squarecell::Point position, int age, char type, int id, int size);
            virtual void update();
    };

    class Collector : public Fourmi {
        private:
            bool carryFood;
        public:
            Collector(squarecell::Point position, int id, int age, bool carryFood);
            void update();
            static std::shared_ptr<fourmi::Fourmi> importFromExtSaveCollector (std::vector<std::string> &inputBuffer,
                                                                               int index);
    };

    class Defensor : public Fourmi {
        public:
            Defensor(squarecell::Point position, int id, int age);
            void update();
            static std::shared_ptr<fourmi::Fourmi> importFromExtSaveDefensor (std::vector<std::string> &inputBuffer,
                                                                              int index);
    };

    class Predator : public Fourmi {
        public:
            Predator(squarecell::Point position, int id, int age);
            void update();
            static std::shared_ptr<fourmi::Fourmi> importFromExtSavePredator (std::vector<std::string> &inputBuffer,
                                                                              int index);
    };

    class Generator : public Fourmi {
        public:
            Generator(squarecell::Point position, int id);
            void update();
            static std::shared_ptr<fourmi::Fourmi> importFromExtSaveGenerator (std::vector<std::string> &inputBuffer,
                                                                               int index);
    };
}

#endif //TCHANZ_FOURMI_H