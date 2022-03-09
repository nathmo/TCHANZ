/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include <iostream>
#include "testsuit.h"
#include "textstorage.h"
#include "textstorage.cc"
#include <vector>
#include <string>

using namespace std;

vector<string> assert_textstorage_readtxt(vector<string>);
//bool assert_textstorage_writetxt();

int main() {
    cout << "test started" << endl;

    assert_textstorage_readtxt(readtxt(no_error_collector_move.txt));

    cout << "test done" << endl;
    return 0;
}

string assert_textstorage_readtxt(vector<string> inputBuffer) {  //t avais mis un vector de string, j pense un string mieux ?
    string teststringdebut = "# Simple test file without error";
    string teststringfin = "\t# predators:";

    if(teststringdebut == inputBuffer[0] and teststringfin == inputBuffer[inputBuffer.size() - 1]) {
        return "C'est tout bon teststorage_readtxt";
    } else {
        return "C'est pas bon teststorage_readtxt";
    }
}


/*
bool assert_textstorage_writetxt() {
    string teststring = "salut test! \n test";
    // use la fonction write de textstorage et write dans un fichier text.txt
    // use la fonction read de textstorage et read dans le fichier text.txt qui viens d'etre ecrit
}
*/