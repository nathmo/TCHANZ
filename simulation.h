/*!
  \file   simulation.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "simulation".
*/

#ifndef TCHANZ_SIMULATION_H
#define TCHANZ_SIMULATION_H

#include <string>
#include "squarecell.h"

namespace simulation {
    class Simulation {

    };

// administrative function outside of class
    squarecell::Squarecell loadFromFile(std::string path);
}
#endif //TCHANZ_SIMULATION_H