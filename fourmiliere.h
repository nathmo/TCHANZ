/*!
  \file   fourmiliere.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmiliere".
*/

#ifndef TCHANZ_FOURMILIERE_H
#define TCHANZ_FOURMILIERE_H

#include "fourmi.h"
#include "squarecell.h"
#include <vector>
#include <memory>

namespace fourmiliere
{
    class Fourmiliere : public squarecell::Entity
    {
    private:
        int foodReserve;
        int nbC;
        int nbD;
        int nbP;
        std::vector<fourmi::Fourmi *> memberAnts;
    public:
        Fourmiliere(squarecell::Point position, squarecell::Point size, int total_food, int nbC, int nbD, int nbP );
        void update();
        static std::shared_ptr<squarecell::Entity> importFromExtSaveGenerator(std::vector<std::string> &inputBuffer);
    };
}

#endif //TCHANZ_FOURMILIERE_H