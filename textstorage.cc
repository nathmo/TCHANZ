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
        if('#' == valeur[0]) break; //passe au suivant
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

vector<squarecell::Entity> textstorage::importDump (vector<vector<string>> inputBuffer_modifie) {
    vector<squarecell::Entity> entityList;
    string quantity_food = inputBuffer_modifie[0][0]; //forcement premiere position c est quantite de bouffe
    int int_quantity_food = stoi(quantity_food);

    for(int i(1); i < int_quantity_food+1; i++);{
        int x = stoi(inputBuffer_modifie[i][1]);
        int y = stoi(inputBuffer_modifie[i][2]);
        entityList.push_back(Nourriture(x,y));
    }

    int intermediaire = int_quantity_food + 2; //position des donnees "grande ligne"
    unsigned int quantity_anthill = stoi(inputBuffer_modifie[intermediaire-1][0]);
    for(int i(0); i < quantity_anthill; i++){
        int collector = stoi(inputBuffer_modifie[intermediaire][6]);
        int defensor = stoi(inputBuffer_modifie[intermediaire][7]);
        int predator = stoi(inputBuffer_modifie[intermediaire][8]);

        for(int c(1); c < collector+1; c++){
            int x = stoi(inputBuffer_modifie[intermediaire+1][0]);
            int y = stoi(inputBuffer_modifie[intermediaire+1][1]);
            int z = stoi(inputBuffer_modifie[intermediaire+1][2]);
            bool condition = (inputBuffer_modifie[intermediaire+1][3]);
            intermediaire = intermediaire + 1;
            entityList.push_back(collector(x,y,z,condition));
        }

        for(int d(1); d < defensor+1; d++){
            int x = stoi(inputBuffer_modifie[intermediaire+1][0]);
            int y = stoi(inputBuffer_modifie[intermediaire+1][1]);

            intermediaire = intermediaire + 1;
            entityList.push_back(defensor(x,y));
        }

        for(int p(1); p < predator+1; p++){
            int x = stoi(inputBuffer_modifie[intermediaire+1][0]);
            int y = stoi(inputBuffer_modifie[intermediaire+1][1]);
            intermediaire = intermediaire + 1;
            entityList.push_back(defensor(x,y));
        }
    }


    // TODO : read the array and create the different entity
    // return a vector of entity (class that every entity (ants, anthill, food) inherit from)
    return entityList;
}

vector<string> textstorage::exportDump (vector<squarecell::Entity> entityArrayDump) {
    vector<string> entityList;
    // TODO : write the array of entity and export it as an array of int (reverse of import)
    return entityList;
}
