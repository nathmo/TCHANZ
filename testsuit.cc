/*!
  \file   testsuit.cc
  \author Nathann Morand et Felipe Ramirez
  \date   MARS 2022
  \brief  Implémentation du module de test avec la seconde fonction main() avec test
*/

#include <iostream>
#include "textstorage.h"
#include "textstorage.cc"
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

bool assert_textstorage_readtxt();
bool assert_textstorage_writetxt();

int main() {
    cout << "beginning unit test" << endl;
    assert(assert_textstorage_readtxt());
    assert(assert_textstorage_writetxt());
    cout << "beginning integration test" << endl;

    cout << "all test passed successfully" << endl;
    return 0;
}

bool assert_textstorage_readtxt() {  //t avais mis un vector de string, j pense un string mieux ?
    int teststringfin = 0;
    vector <int> inputBuffer = textstorage::readtxt("scenario/no_error_collector_move.txt");
    if(teststringfin == inputBuffer[inputBuffer.size() - 1]) {
        return true;
    } else {
        //cout << teststringfin <<endl;
        //cout << inputBuffer[inputBuffer.size() - 1] <<endl;
        return false;
    }
}



bool assert_textstorage_writetxt() {      //t avais mis un bool de base
    vector <int> teststring = {1,2,3,4,56,-6,2};
    string Stockage_fichiertxt = "scenario/test_ecriture.txt";
    textstorage::writetxt(Stockage_fichiertxt, teststring);
    vector <int> inputBuffer = textstorage::readtxt(Stockage_fichiertxt);
    bool passed = true;
    for(int i=0; i<teststring.size();i++)
    {
        if (teststring[i] != inputBuffer[i])
        {
            passed = false;
        }
    }
    if(passed)
    {
        return true;
    } else {
        cout << "expected : " + to_string(teststring[0]) << endl;
        cout << "received : " + to_string(inputBuffer[0]) << endl;
        cout << "expected : " + to_string(teststring[4]) << endl;
        cout << "received : " + to_string(inputBuffer[4]) << endl;
        cout << "expected : " + to_string(teststring[5]) << endl;
        cout << "received : " + to_string(inputBuffer[5]) << endl;
        cout << "expected : " + to_string(teststring[6]) << endl;
        cout << "received : " + to_string(inputBuffer[6]) << endl;
        return false;
    }
}
