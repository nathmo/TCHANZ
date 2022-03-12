//
// Created by felip on 06.03.2022.
//
#include "textstorage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void textstorage::writetxt(string filename, vector<string> lineToWrite){
    fstream txtsave;
    string line;
    txtsave.open(filename, ios::out);//out ca ecrit dans un fichier extern
    if(txtsave.fail()) {
        cout << "soucis writetxt_filename" << endl;
        exit(EXIT_FAILURE);
    }
    else if(txtsave.is_open()) {
        for(unsigned int i=0; i<lineToWrite.size();i++) {
            line = lineToWrite[i]; //inserting text
            txtsave << line;
        }
        txtsave.close(); //close the file object
    }
}

vector<int> textstorage::readtxt(string filename){  //sans espace ni qqch begin #
    fstream txtsave;
    string line;
    vector<int> inputBuffer_modifie;
    txtsave.open(filename,ios::in);//in car tu lis depuis fichier
    if(txtsave.fail()){
        cout << "soucis readtxt_filename" << endl;
        exit(EXIT_FAILURE);
    }
    else if(txtsave.is_open()){   //checking whether the file is open
        while(getline(txtsave >> ws, line)){ // avec ws j ai plus les tab ou les espaces avant premier caractere
            if(line[0]=='#') continue;
            vector<int> lineBuffer = creation(line);
            inputBuffer_modifie.insert(inputBuffer_modifie.end(),lineBuffer.begin(),lineBuffer.end());
        }
        txtsave.close();
    }
    return inputBuffer_modifie;
}

vector<int> textstorage::creation (string line){
    istringstream iss(line);
    vector<int> tableauValeur;
    int valeur;
    while(iss >> valeur){
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

//TODO:  import


