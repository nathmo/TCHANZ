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

vector<vector<string>> textstorage::readtxt (string filename) {  //sans espace ni qqch begin #
    fstream txtsave;
    string line;
    vector<vector<string>> inputBuffer_modifie;
    txtsave.open(filename,ios::in);//in car tu lis depuis fichier
    if(txtsave.fail()) {
        cout << "soucis readtxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {   //checking whether the file is open
        while(getline(txtsave >> ws, line)) { // avec ws j ai plus les tab ou les espaces avant premier caractere
            if(line[0]=='#') continue;
            vector<string> lineBuffer = creation(line);
            inputBuffer_modifie.push_back(lineBuffer);
        }
        txtsave.close();
    }
    return inputBuffer_modifie;
}

vector<string> textstorage::creation (string line) {
    istringstream iss(line);
    vector<string> tableauValeur;
    string valeur;
    while(iss >> valeur) {
        if('#' == valeur[0]) break; //pas sur que ca soit ça si t arrive a me confirmer
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
