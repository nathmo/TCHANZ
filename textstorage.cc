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

/*
void writetxt(string filename, vector<string> lineToWrite) {
    fstream txtsave; // cr
    string line;
    txtsave.open(filename, ios::out); //out ca ecrit dans un fichier extern
    if(txtsave.is_open()) {
        for(int i=0; i<lineToWrite.size();i++) {
            line = lineToWrite[i]; //inserting text
            txtsave << line;
        }
        txtsave.close(); //close the file object
    }
}
*/

fstream writetxt(string filename, vector<string> lineToWrite) {
    fstream txtsave; // cr
    string line;
    txtsave.open(filename, ios::out); //out ca ecrit dans un fichier extern
    if(txtsave.is_open()) {
        for(int i=0; i<lineToWrite.size();i++) {
            line = lineToWrite[i]; //inserting text
            txtsave << line;
        }
        txtsave.close(); //close the file object
    }
    return txtsave;
}
salut
//TODO : validade
//TODO:  import

vector<string> readtxt(string filename){
    fstream txtsave;
    string line;
    vector<string> inputBuffer;
    txtsave.open(filename,ios::in); //in car tu lis depuis fichier
    if(txtsave.is_open()){   //checking whether the file is open
        while(getline(txtsave, line)){ //read data from file object and put it into string.
            inputBuffer.push_back(line);
        }
        txtsave.close();   //close the file object.
    }
    return inputBuffer;
}
