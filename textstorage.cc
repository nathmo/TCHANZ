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

void writetxt(string filename, vector<string> lineToWrite){
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

vector<int> creation (string line){
    istringstream iss(line);
    vector<int> tableauValeur;
    int valeur;

    while(iss >> valeur){
        tableauValeur.push_back(valeur);
    }
    return tableauValeur;
}

//TODO:  import

vector<int> readtxt_modifie_sans_espace(string filename){  //sans espace ni qqch begin #
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
        txtsave.close();   //close the file object.
    }
    return inputBuffer_modifie;
}


/*

vector<string> readtxt(string filename){
    fstream txtsave;
    string line;
    vector<string> inputBuffer;
    txtsave.open(filename,ios::in);//in car tu lis depuis fichier
    if(txtsave.fail()) {
        cout << "soucis readtxt_filename" << endl;
        exit(EXIT_FAILURE);
    }
    if(txtsave.is_open()){   //checking whether the file is open
        while(getline(txtsave, line)){ // avec ws j ai plus les tab ou les espaces avant premier caractere
            inputBuffer.push_back(line);
        }
        txtsave.close();   //close the file object.
    }
    return inputBuffer;
}


 void validation(vector<string> inputBuffer_modifie){
    STATE state(FOOD);
    unsigned int i(0);

    while(i<inputBuffer_modifie.size()){
        if(state == FOOD){
            recuperation_check(inputBuffer.modifie[i], state); //doit verifier si bien des int et plus tard renvoyer une array
            i++;
        }
        if(state == ANTHILL){
            recuperation_check(inputBuffer.modifie[i], state); //doit verifier si bien des int et plus tard renvoyer une array
            i++;
        }
        if(state == COLLECTOR){
            recuperation_check(inputBuffer.modifie[i], state);
            i++;
        }
        if(state == PREDATOR){
            recuperation_check(inputBuffer.modifie[i], state);
            i++;
        }
    }
}

void recuperation_check(string line_inputBuffer_modifie, STATE& state){
    vector<int> recuperation;


    if(){

    }

    recuperation.push_back(valeur);
}

void changement_etat(STATE& state){
    if (state == FOOD)
        state = ANTHILL;
    if (state == ANTHILL)
        state = COLLECTOR;
    if (state == COLLECTOR)
        state = PREDATOR;
    if (state == PREDATOR){  // faut check si on a fait toutes les fourmilieres

    }
}