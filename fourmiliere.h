/*!
  \file   fourmiliere.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  prototype du module "fourmiliere".
*/

#ifndef TCHANZ_FOURMILIERE_H
#define TCHANZ_FOURMILIERE_H

#import "fourmi.h"

namespace fourmiliere
{
    class Fourmiliere : public Entity
    {
    private:
        int foodReserve;
        int nbC;
        int nbD;
        int nbP;
        vector<fourmi::Fourmi *> memberAnts;
    public:
        Fourmiliere(Point position, Point size, int total_food, int nbC, int nbD, int nbP );
        update();
    };
}

#endif //TCHANZ_FOURMILIERE_H