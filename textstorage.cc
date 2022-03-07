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
    fstream txtsave; // cr
    txtsave.open(filename, ios::out); //out ca ecrit dans un fichier extern
    if (txtsave.is_open()) {
        while (lineToWrite.size() > 0) {
            txtsave << lineToWrite.pop_back(); //inserting text
        }
        txtsave.close(); //close the file object
    }
}

//TODO : validade
//TODO:  import

vector<string> readtxt(string filename){
    fstream txtsave;
    string line;
    vector<string> inputBuffer;
    txtsave.open(filename,ios::in); //in car tu lis depuis fichier
    if (txtsave.is_open()){   //checking whether the file is open
        while(getline(txtsave, line)) //read data from file object and put it into string.
            inputBuffer.push_back(line);
        }
        txtsave.close();   //close the file object.
    }
    return inputBuffer;
}
