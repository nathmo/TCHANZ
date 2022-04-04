/*!
  \file   fourmiliere.h
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  prototype du module "fourmiliere".
*/
#ifndef TCHANZ_FOURMILIERE_H
#define TCHANZ_FOURMILIERE_H

#include <vector>
#include <memory>
#include "fourmi.h"
#include "entity.h"
#include "squarecell.h"

class Fourmiliere : public Entity {
private:
    int foodReserve;
    int nbC;
    int nbD;
    int nbP;
    std::vector<std::shared_ptr<Fourmi>> memberAnts;

public:
    Fourmiliere(Point position, int size, int totalFood,
                int nbC, int nbD, int nbP, int id,
                std::vector<std::shared_ptr<Fourmi>> FourmiList);
    virtual void update();
    // export the entity to something that can be written in a file
    virtual std::vector<std::vector<std::string>> export();
    // bundle all the check used to validate the anthill content
    void check();
    // remplace the list of member ants
    void overrideAnts(std::vector<std::shared_ptr<Fourmi>> FourmiList);
    // check that the Generator are in the anthill
    void checkGeneratorUsingCoord();
    // same for defensor
    void checkDefensorUsingCoord();
    // create an anthill object from a vector of string + run the check for the anthil
    static std::shared_ptr<Fourmiliere> importFromExtSaveFourmilliere(
            std::vector<std::string> &inputBuffer, int index,
            std::vector<std::shared_ptr<Fourmi>> FourmiList,
            std::vector<std::shared_ptr<Fourmiliere>> previousAnthill);
    int getFoodReserve();
    int getNbC();
    int getNbD();
    int getNbP();

};

#endif //TCHANZ_FOURMILIERE_H