/*!
  \file   fourmiliere.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "fourmiliere".
*/


#include "fourmiliere.h"
#include "entity.h"
#include "squarecell.h"
#include "constantes.h"
#include <iostream>
#include <memory>
using namespace std;

fourmiliere::Fourmiliere::Fourmiliere(squarecell::Point position,int size,int total_food,int nbC,int nbD,int nbP,int id, vector<shared_ptr<fourmi::Fourmi>> FourmiList) :
        entity::Entity(position, size, size, fourmilliereCST, id, false)
{
    foodReserve = total_food;
    this->nbC=nbC;
    this->nbD=nbD;
    this->nbP=nbP;
    memberAnts = FourmiList;
}

void fourmiliere::Fourmiliere::update()
{

}

shared_ptr<entity::Entity> fourmiliere::Fourmiliere::importFromExtSaveGenerator(vector<string> &inputBuffer, int index,
                                                                                vector<shared_ptr<fourmi::Fourmi>> FourmiList)
{
    if(inputBuffer.size()<9)
    {
        cout << "fourmilliere : number of argument mismatch" << endl;
        exit(EXIT_FAILURE);
    }else{
        int x = stoi(inputBuffer[0]);
        int y = stoi(inputBuffer[1]);
        int size = stoi(inputBuffer[2]);
        int total_food = stoi(inputBuffer[5]);
        int nbC = stoi(inputBuffer[6]);
        int nbD = stoi(inputBuffer[7]);
        int nbP = stoi(inputBuffer[8]);

        return make_shared<fourmiliere::Fourmiliere>(squarecell::Point(x,y), size,total_food,nbC,nbD,nbP,index, FourmiList);
    }
}