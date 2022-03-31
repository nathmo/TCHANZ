/*!
  \file   fourmiliere.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmiliere".
*/

#ifndef TCHANZ_FOURMILIERE_H
#define TCHANZ_FOURMILIERE_H

#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"
#include <vector>
#include <memory>

namespace fourmiliere {
    class Fourmiliere : public entity::Entity {
    private:
        int foodReserve;
        int nbC;
        int nbD;
        int nbP;
        std::vector<std::shared_ptr<fourmi::Fourmi>> memberAnts;

    public:
        Fourmiliere(squarecell::Point position,int size,int total_food,int nbC,int nbD,int nbP,int id,
                    std::vector<std::shared_ptr<fourmi::Fourmi>> FourmiList);
        void update();
        void overrideAnts(std::vector<std::shared_ptr<fourmi::Fourmi>> FourmiList);
        static std::shared_ptr<fourmiliere::Fourmiliere> importFromExtSaveFourmilliere(std::vector<std::string> &inputBuffer, int index,
                                                                          std::vector<std::shared_ptr<fourmi::Fourmi>> FourmiList);
    };
}

#endif //TCHANZ_FOURMILIERE_H