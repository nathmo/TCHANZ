/*!
  \file   textstorage.cc
  \author Nathann Morand (10%) et Felipe Ramirez (90%)
  \date   MARS 2022
  \brief  implémentation du module "textstorage".
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "textstorage.h"
#include "fourmi.h"
#include "fourmiliere.h"
#include "nourriture.h"


using namespace std;

void TextStorage::importTXT(std::string filename,
               vector<shared_ptr<Nourriture>> &foodVectorReturn,
               vector<shared_ptr<Fourmiliere>> &fourmilliereVectorReturn){
    TextStorage::importDump(TextStorage::readtxt(filename),
                            foodVectorReturn, fourmilliereVectorReturn);
}

void TextStorage::exportTXT(std::string filename,
                      vector<shared_ptr<Entity>> entityToExport){
    TextStorage::writetxt(filename, TextStorage::exportDump(entityToExport));
}

void TextStorage::writetxt(string filename, vector<vector<string>> lineToWrite) {
    fstream txtsave;
    txtsave.open(filename, ios::out);//open file with write access
    if(txtsave.fail()) {
        cout << "soucis writetxt_filename" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) {
        for(unsigned int i=0; i<lineToWrite.size();i++) {
            string line =""; // dump each line (add space as its a vector of word)
            for(unsigned int j=0; j<lineToWrite[i].size();j++) {
                line = line + " " + lineToWrite[i][j];
            }
            txtsave << line << endl;
        }
        txtsave.close();
    }
}

vector<vector<string>> TextStorage::readtxt(string filename) {
    fstream txtsave;
    string line;
    vector<vector<string>> inputBuffer;
    txtsave.open(filename,ios::in); //open file with read access
    if(txtsave.fail()) {
        cout << "Fichier non ouvrable ou pas assez de droit" << endl;
        exit(EXIT_FAILURE);
    } else if(txtsave.is_open()) { //checking whether the file is open
        while(getline(txtsave >> ws, line)) {//tokenize each line as a vector of word
            if(line[0]=='#') continue;
            vector<string> lineBuffer = tokenize(line);
            inputBuffer.push_back(lineBuffer);
        }
        txtsave.close();
    }
    return inputBuffer;
}

vector<string> TextStorage::tokenize(string line) {
    istringstream iss(line);
    vector<string> tableauValeur;
    string valeur;
    while(iss >> valeur) {
        if('#' == valeur[0]) break; //passe au suivant
        if(valeur == "") continue;
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

void TextStorage::importDump(vector<vector<string>> inputBuffer,
                             vector<shared_ptr<Nourriture>> &foodVectorReturn,
                          vector<shared_ptr<Fourmiliere>> &fourmilliereVectorReturn) {
    if(not(checksizeLine(inputBuffer))) {
        exit(0); // ensure there is enough argument in the file, exit otherwise
    }
    unsigned int QuantityFood = stoi(inputBuffer[0][0]);
    TextStorage::importFood(inputBuffer, foodVectorReturn);
    unsigned int intermediaire = QuantityFood + 2; //index de la ligne dans le fichier
    unsigned int quantityAnthill = stoi(inputBuffer[intermediaire-1][0]);
    for(unsigned int i(0); i < quantityAnthill; i++) {
        unsigned int collector = stoi(inputBuffer[intermediaire][6]);
        unsigned int defensor = stoi(inputBuffer[intermediaire][7]);
        unsigned int predator = stoi(inputBuffer[intermediaire][8]);
        unsigned int indexFourmilliere = i, indexFourmi = i;
        vector<shared_ptr<Fourmi>>  fourmilliereMemberList; //ant of each anthill
        vector<string> FourmilliereConfig = inputBuffer[intermediaire];
        shared_ptr<Fourmiliere> Fourmilliere = // create+validate the anthill ptr
                Fourmiliere::importFromExtSaveFourmilliere(FourmilliereConfig,
                                                           indexFourmilliere,
                                                           fourmilliereMemberList,
                                                           fourmilliereVectorReturn);
        fourmilliereVectorReturn.push_back(Fourmilliere);
        fourmilliereMemberList.push_back(Generator::importFromExtSaveGenerator(
                                             inputBuffer[intermediaire],indexFourmi));
        for(unsigned int c(1); c < collector+1; c++, intermediaire++) { // add Collect
            fourmilliereMemberList.push_back(Collector::importFromExtSaveCollector(
                                          inputBuffer[intermediaire+1], indexFourmi));
        }
        for(unsigned int d(1); d < defensor+1; d++, intermediaire++) { // add defensor
            fourmilliereMemberList.push_back(Defensor::importFromExtSaveDefensor(
                                          inputBuffer[intermediaire+1], indexFourmi));
        }
        for(unsigned int p(1); p < predator+1; p++, intermediaire++) { // add defensor
            fourmilliereMemberList.push_back(Predator::importFromExtSavePredator(
                                          inputBuffer[intermediaire+1], indexFourmi));
        }
        (*Fourmilliere).overrideAnts(fourmilliereMemberList);// modify anthill with
        intermediaire = intermediaire+1;                     // its ants + run checks
    }
}

vector<vector<string>> TextStorage::exportDump(
                                            vector<shared_ptr<Entity>> listOfEntity) {
    vector<vector<string>> toExport = {{"0"}};
    int nOfFood=0;
    for(auto entity:listOfEntity){
        vector<vector<string>> temp = (*entity).exportToString();
        toExport.insert(toExport.end(), temp.begin(), temp.end());
        if((*entity).getSpecie() == nourritureCST) {
            nOfFood++;
        }
    }
    toExport[0][0]=to_string(nOfFood);
    return toExport;
}

bool TextStorage::checksizeLine(vector<vector<string>> intArrayDump) {
    bool status = true;
    string strQuantityFood = intArrayDump[0][0];
    unsigned int QuantityFood = stoi(strQuantityFood);
    for(unsigned int i(1); i < QuantityFood+1; i++) {
        if(intArrayDump[i].size()<2) {
            cout << "not enough argument on a line from the file at index : "
                    + to_string(i) << endl;
            status = false;
        }
    }
    unsigned int intermediaire = QuantityFood + 2; //index des donnees (line)
    unsigned int quantityAnthill = stoi(intArrayDump[intermediaire-1][0]);
    for(unsigned int i(0); i < quantityAnthill; i++) {
        if(intArrayDump.size()<intermediaire) {
            cout << "not enough line from the file"<< endl;
            status = false;
        }
        if(intArrayDump[intermediaire].size()<9) {
            cout << "not enough argument on a line from the file at index : "
                    + to_string(intermediaire) << endl;
            status = false;
        }
        int collector = stoi(intArrayDump[intermediaire][6]);
        int defensor = stoi(intArrayDump[intermediaire][7]);
        int predator = stoi(intArrayDump[intermediaire][8]);
        if(intArrayDump.size()<(intermediaire+collector+defensor+predator)) {
            cout << "not enough argument on a line from the file at index : "
                    + to_string((intermediaire+collector+defensor+predator)) << endl;
            status = false;
        }
    }
    return status;
}

void TextStorage::importFood(vector<vector<string>> inputBuffer,
                       vector<shared_ptr<Nourriture>> &foodVectReturn){
    unsigned int QuantityFood = stoi(inputBuffer[0][0]);
    for(unsigned int i(1); i < QuantityFood+1; i++) {//ajoute la nourriture au vecteur
        int index = i;
        foodVectReturn.push_back(Nourriture::importFromExtSave(inputBuffer[i],
                                                                 index));
    }
}