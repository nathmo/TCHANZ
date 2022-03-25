/*!
  \file   textstorage.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  implémentation du module "textstorage".
*/
#include "textstorage.h"
#include "squarecell.h"
#include "fourmi.h"
#include "fourmiliere.h"
#include "nourriture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

void textstorage::writetxt (string filename, vector<vector<string>> lineToWrite) {
    fstream txtsave;
    txtsave.open(filename, ios::out);//out ca ecrit dans un fichier extern
    if(txtsave.fail()) {
        cout << "soucis writetxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {
        for(unsigned int i=0; i<lineToWrite.size();i++)
        {
            string line ="";
            for(unsigned int j=0; j<lineToWrite[i].size();j++)
            {
                line = line + " " + lineToWrite[i][j];
            }
            txtsave << line << endl;
        }
        txtsave.close();
    }
}

vector<vector<string>> textstorage::readtxt (string filename) { //sans espace ni qqch begin #
    fstream txtsave;
    string line;
    vector<vector<string>> inputBuffer;
    txtsave.open(filename,ios::in);//in car tu lis depuis fichier
    if(txtsave.fail()) {
        cout << "soucis readtxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {   //checking whether the file is open
        while(getline(txtsave >> ws, line)) { // avec ws j ai plus les tab ou les espaces avant premier caractere
            if(line[0]=='#') continue;
            vector<string> lineBuffer = creation(line); //tokenize each line as a vector of word
            inputBuffer.push_back(lineBuffer);
        }
        txtsave.close();
    }
    return inputBuffer;
}

vector<string> textstorage::creation (string line) {
    istringstream iss(line);
    vector<string> tableauValeur;
    string valeur;
    while(iss >> valeur) {
        if('#' == valeur[0]) break; //passe au suivant
        if(valeur=="") continue;
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

vector<shared_ptr<squarecell::Entity>> textstorage::importDump (vector<vector<string>> inputBuffer) {
    vector<shared_ptr<squarecell::Entity>>  entityList;
    string quantity_food = inputBuffer[0][0];
    int int_quantity_food = stoi(quantity_food);
    for(int i(1); i < int_quantity_food+1; i++) {
        entityList.push_back(nourriture::Nourriture::importFromExtSaveFood(inputBuffer[i]));
    }

    int intermediaire = int_quantity_food + 2; //position des donnees "grande ligne"
    unsigned int quantity_anthill = stoi(inputBuffer[intermediaire-1][0]);
    for(unsigned int i(0); i < quantity_anthill; i++) {
        int collector = stoi(inputBuffer[intermediaire][6]);
        int defensor = stoi(inputBuffer[intermediaire][7]);
        int predator = stoi(inputBuffer[intermediaire][8]);
        
        importFromExtSaveGenerator const({inputBuffer[intermediaire][3],inputBuffer[intermediaire][4]});
      
        for(int c(1); c < collector+1; c++) {
            importFromExtSaveCollector const(inputBuffer[intermediaire+c]);
            intermediaire = intermediaire+1; 
        }
        
        for(int d(1); d < defensor+1; d++) {
            importFromExtSaveDefensor const(inputBuffer[intermediaire+d]);
            intermediaire = intermediaire + 1;
        }
        
        for(int p(1); p < predator+1; p++) {
            importFromExtSavePredator const(inputBuffer[intermediaire+p]);
            intermediaire = intermediaire+1;
        }
    }
    return entityList;
}

vector<vector<string>> textstorage::exportDump (vector<shared_ptr<squarecell::Entity>> entityArrayDump) {
    vector<vector<string>> entityList;
    // TODO : write the array of entity and export it as an array of int (reverse of import)
    return entityList;
}

bool textstorage::checksize_line(int int_quantity_food, int ){

}