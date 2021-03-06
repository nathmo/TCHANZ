/*!
  \file   simulation.h
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  prototype du module "simulation".
*/
#ifndef TCHANZ_SIMULATION_H
#define TCHANZ_SIMULATION_H

#include <string>
#include <memory>
#include <vector>
#include "entity.h"
#include "nourriture.h"
#include "fourmiliere.h"

class Simulation {
private:
    std::vector<std::shared_ptr<Nourriture>> nourritureList;
    std::vector<std::shared_ptr<Fourmiliere>> anthillList;

public:
    Simulation();
    std::vector<std::shared_ptr<Entity>> getListEntity();
    void loadFromFile(std::string path);
    void saveToFile(std::string path);
    void simulateStep();
    void refreshGUI();
    int getFoodNb();
    int getAnthNb();
    std::vector<double> getAnthInfoStat(int id);
};

#endif //TCHANZ_SIMULATION_H