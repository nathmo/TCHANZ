/*!
  \file   textstorage.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "textstorage".
*/
#include "textstorage.h"
#include "squarecell.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void textstorage::writetxt (string filename, vector<int> lineToWrite) {
    fstream txtsave;
    string line;
    txtsave.open(filename, ios::out);//out ca ecrit dans un fichier extern
    if(txtsave.fail()) {
        cout << "soucis writetxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {
        for(unsigned int i=0; i<lineToWrite.size();i++) {
            line = (" "+to_string(lineToWrite[i])+" ");
            txtsave << line;
        }
        txtsave.close();
    }
}

vector<int> textstorage::readtxt(string filename) {  //sans espace ni qqch begin #
    fstream txtsave;
    string line;
    vector<int> inputBuffer_modifie;
    txtsave.open(filename,ios::in);//in car tu lis depuis fichier
    if(txtsave.fail()) {
        cout << "soucis readtxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {   //checking whether the file is open
        while(getline(txtsave >> ws, line)) { // avec ws j ai plus les tab ou les espaces avant premier caractere
            if(line[0]=='#') continue;
            vector<int> lineBuffer = creation(line);
            inputBuffer_modifie.insert(inputBuffer_modifie.end(),lineBuffer.begin(),lineBuffer.end());
        }
        txtsave.close();
    }
    return inputBuffer_modifie;
}

vector<int> textstorage::creation (string line) {
    istringstream iss(line);
    vector<int> tableauValeur;
    int valeur;
    while(iss >> valeur) {
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

vector<squarecell::Entity> textstorage::importDump (vector<int> intArrayDump) {
    vector<squarecell::Entity> entityList;
    // TODO : read the array and create the different entity
    // return a vector of entity (class that every entity (ants, anthill, food) inherit from)
    return entityList;
}

vector<int> textstorage::exportDump (vector<squarecell::Entity> entityArrayDump) {
    vector<int> entityList;
    // TODO : write the array of entity and export it as an array of int (reverse of import)
    return entityList;
}

bool textstorage::assert_vector_size(vector<int> inputBuffer_modifie) {
    int valeur_food = inputBuffer_modifie[0];
    unsigned int valeur_anthill(0);
    int valeur_intermediaire(0);
    unsigned int nombre_attendu(1); //on prend deja en compte qu il y a le chiffre du nombre de anthill

    valeur_anthill = inputBuffer_modifie[(valeur_food * 2) + 1];//+1 car on veut anthill
    valeur_intermediaire = (valeur_food * 2) + 1; //se trouve au point de quantite de anthill
    for(unsigned int i(0); i < valeur_anthill; i++) {
        nombre_attendu = nombre_attendu + calcul(inputBuffer_modifie, valeur_intermediaire);
    }

    nombre_attendu = ((valeur_food*2) + 1) + (9*valeur_anthill) + nombre_attendu;  //valeur bouffe + valeur variable chaque anthill + addition diff fourmis
    if(nombre_attendu == inputBuffer_modifie.size()) {
        return true;
    } else {
        return false;
    }
}


int textstorage::calcul(vector<int> inputBuffer_modifie, int& valeur_intermediaire) {
    int Collector(0);
    int Defensor(0);
    int Predator(0);
    int total(0);

    Collector = inputBuffer_modifie[(valeur_intermediaire) + 7];
    Defensor = inputBuffer_modifie[(valeur_intermediaire) + 8];
    Predator = inputBuffer_modifie[(valeur_intermediaire) + 9];

    total = 3*(Collector + Defensor + Predator);
    valeur_intermediaire = (valeur_intermediaire + 9) + total; //intermediaire = position predator + total pour arriver a la derniere info de predator

    return total;
}