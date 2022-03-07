//
// Created by felip on 06.03.2022.
//

#include "textstorage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void writetxt(string filename, vector<string> lineToWrite) {
    fstream txtsave;
    txtsave.open(filename, ios::out); //out ca ecrit dans un fichier extern

    if (txtsave.is_open()) {
        while () {
            txtsave
                    << "write each string here : iterrate over the string lsit"; //inserting text
            txtsave.close(); //close the file object
        }
    }
}

//TODO : validade
//TODO:  import

vector<string> readtxt(string filename){
    fstream txtsave;
    string line;
    txtsave.open(filename,ios::in); //in car tu lis depuis fichier

    if (txtsave.is_open()){   //checking whether the file is open
        while(getline(txtsave, line)) //read data from file object and put it into string.
            istringstream iss(line);
            string phrase;
            txtsave.push_back(line);   //print the data of the string
        }
        txtsave.close();   //close the file object.
    }
}

void ecriture(fstream txtsave) {
    fstream txtsave;
    string phrase;
    txtsave.open(filename, ios::out);

    if (txtsave.is_open()) {
        while(txtsave >> phrase)

        txtsave.is_close();
    }
}

void lecture (......) {
    fstream txtsave;
    string line;
    txtsave.open(filename,ios::in);

    if (txtsave.is_open()) {
        while (getline(txtsave, line) {
            txtsave.push_back(line);
        }
        txtsave.close();
    }
}
