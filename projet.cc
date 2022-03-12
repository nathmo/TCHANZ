/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module principal avec la fonction main()
*/

#include <iostream>
#include "simulation.h"

using namespace std;

int main (int argc, char *argv[])
{
    if(argc < 2) // delete once GUI is setup
    {
        cout << "Please provide a file to load" << endl;
        return 0;
    }
    simulation::loadFromFile(string( argv[1]));
    return 0;
}