/*!
  \file   projet.cc
  \author Nathann Morand (100%) et Felipe Ramirez (0%)
  \date   MARS 2022
  \brief  implémentation du module principal avec la fonction main()
*/
#include <iostream>
#include "simulation.h"
#include "gui.h"

using namespace std;

int main(int argc, char *argv[]);
void startHeadless(string path);
void startGui(string path);

int main(int argc, char *argv[]) {
    string path = "";
    if(argc > 2) {
        string headlessKeyword = "--headless";
        bool status = true;
        for(int i(0); i < 10; i++) {
            if(not(argv[2][i] == headlessKeyword.at(i))) {
                status = false;
            }
        }
        if(status) { // allow for operation without GUI, for debug/test purpose
            startHeadless(argv[1]);
            return 0;
        } else {
            cout << "wrong argument provided" << endl;
            cout << "syntax example : ./projet t01.txt" << endl;
            cout << "syntax example for no GUI : ./projet t01.txt --headless" << endl;
        }
    } else if (argc == 2){
        path = argv[1];
        startGui(path);
    } else {
        startGui(path);
    }
    return 0;
}

void startHeadless(string path) {
    shared_ptr<Simulation> simulatiom = make_shared<Simulation>();
    (*simulatiom).loadFromFile(path);
    //Simulation::simulateStep(entityList);
    //Simulation::saveToFile(path+"Plus1Step",entityList);
}

void startGui(string path) {
    shared_ptr<Simulation> simulatiom = make_shared<Simulation>();
    if(path != "") {
        (*simulatiom).loadFromFile(path);
    }
    Gui::window(simulatiom);
}