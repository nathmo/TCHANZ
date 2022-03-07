/*!
  \file   calendrier.h
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Interface du module "squarecell"
*/

#ifndef TCHANZ_SQUARECELL_H
#define TCHANZ_SQUARECELL_H

#endif //TCHANZ_SQUARECELL_H

class Squarecell{
private:
    int g_max;
    vector<vector<bool>> grid;

public:
    Squarecell(int gmax){
        g_max = gmax;
        grid = (vector<vector<bool>> tableau2D(g_max, vector<bool>(g_max)));
    }
    int getG_max(){
        return gmax;
    }
    // TODO : fonction pour ajouter un carré a la grille
    // TODO : fonction pour enlevé un carré de la grille
    // TODO : fonction pour checker les dimmension d'un carré
    // TODO : fonction pour checker la hitbox d'un carré
    // TODO : fonction pour checker si 2 carré se superpose sur la grille
    // TODO : fonction pour chercher si 2 carré se superpose (coord only, methode de classe et pas d'instance)
};