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

class Fourmiliere : public Entity {
private:
    int foodReserve;
    int nbC;
    int nbD;
    int nbP;
    std::vector<std::shared_ptr<Fourmi>> memberAnts;

public:
    Fourmiliere(Point position, int size, int total_food,
                int nbC, int nbD, int nbP, int id,
                std::vector<std::shared_ptr<Fourmi>> FourmiList);
    void update();
    void check();
    void overrideAnts(std::vector<std::shared_ptr<Fourmi>> FourmiList);
    void checkGenerator();
    void checkDefensor() ;
    void checkGeneratorUsingCoord();
    void checkDefensorUsingCoord() ;
    static std::shared_ptr<Fourmiliere> importFromExtSaveFourmilliere(
            std::vector<std::string> &inputBuffer, int index,
            std::vector<std::shared_ptr<Fourmi>> FourmiList);
};

#endif //TCHANZ_FOURMILIERE_H