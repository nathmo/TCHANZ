/*!
  \file   projet.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module principal avec la fonction main()
*/

#include <iostream>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2) // delete once GUI is setup
    {
        cout << "Please provide a file to load" << endl;
        return 0;
    }
    vector<shared_ptr<entity::Entity>> entityVect(simulation::loadFromFile(string(argv[1])));
    for(auto entity: entityVect)
    {
        //cout << (*entity).getSpecie() << endl;
    }
    return 0;
}