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
    if(argc < 2) {
        cout << "Please provide a file to load" << endl;
        return 0;
    }
    if(argc > 2) {
        string headlessKeyword = "--headless";
        bool status = true;
        //cout << "test1" << endl;
        for(int i = 0;i<10;i++){
            if(not(argv[2][i] == headlessKeyword.at(i))) {
                status = false;
            }
        }
        if (status) { // allow for operation without GUI
            startHeadless(argv[1]);
            return 0;
        }
    }
    startGui(argv[1]);
    return 0;
}

void startHeadless(string path) {
    shared_ptr<Simulation> simulatiom = make_shared<Simulation>(path);
    (*simulatiom).loadFromFile();
    //Simulation::simulateStep(entityList);
    //Simulation::saveToFile(path+"Plus1Step",entityList);
}

void startGui(string path) {
    shared_ptr<Simulation> simulatiom = make_shared<Simulation>(path);
    Gui::window(simulatiom);
}