/*!
  \file   gui.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implementation du module "gui".
*/

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <iostream>
#include "gui.h"
#include "graphic.h"
#include "simulation.h"

using namespace std;


void Gui::on_button_clicked_Exit(){
    hide(); //to close the application.
}
void Gui::on_button_clicked_Open(){
    cout << "open" << endl;
    (*simulationPtr).loadFromFile();
}
void Gui::on_button_clicked_Save(){
    cout << "save" << endl;
    (*simulationPtr).saveToFile();
}
void Gui::on_button_clicked_StartStop(){
    if(m_Button_StartStop.get_label()=="start"){
        m_Button_Step.set_sensitive(false);
        m_Button_StartStop.set_label("stop");
        cout << "start" << endl;
    } else if (m_Button_StartStop.get_label()=="stop") {
        m_Button_Step.set_sensitive(true);
        m_Button_StartStop.set_label("start");
        cout << "stop" << endl;
    }
}
void Gui::on_button_clicked_Step(){
    if(m_Button_StartStop.get_label()=="start")
    { // step only if not actively simulating
        cout << "step" << endl;
        (*simulationPtr).simulateStep();
    }
}
void Gui::on_button_clicked_Previous(){
    cout << "previous" << endl;
}
void Gui::on_button_clicked_Next(){
    cout << "next" << endl;
}

Gui::Gui(shared_ptr<Simulation> simulation) :
        graphic(simulation),
        m_box_Gui(Gtk::ORIENTATION_HORIZONTAL),
        m_box_command(Gtk::ORIENTATION_VERTICAL),
        m_Box_General(Gtk::ORIENTATION_VERTICAL),
        m_Box_FoodInfo(Gtk::ORIENTATION_VERTICAL),
        m_Box_AnthInfo(Gtk::ORIENTATION_VERTICAL),
        m_Label_General("General"),
        m_Label_FoodInfo("Info"),
        m_Label_FoodInfoValue("Nb food: 0"),
        m_Label_AnthInfo("Anthill Info"),
        m_Label_AnthInfoValue("None selected"),
        m_Button_Exit("exit"),
        m_Button_Open("open"),
        m_Button_Save("save"),
        m_Button_StartStop("start"),
        m_Button_Step("step"),
        m_Button_Previous("previous"),
        m_Button_Next("next")
{
    simulationPtr = simulation;
    // Set title and border of the window
    set_title("layout buttons");
    set_border_width(0);

    // Add outer box to the window (because the window
    // can only contain a single widget)
    add(m_box_Gui);

    //Put the inner boxes and the separator in the outer box:
    m_box_Gui.pack_start(graphic);
    m_box_Gui.pack_start(m_box_command, false, true);

    m_box_command.pack_start(m_Box_General, false, true);
    m_box_command.pack_start(m_Box_FoodInfo, false, true);
    m_box_command.pack_start(m_Box_AnthInfo, false, true);

    m_Box_General.pack_start(m_Label_General, false, true);
    m_Box_General.pack_start(m_Button_Exit, false, true);
    m_Box_General.pack_start(m_Button_Open, false, true);
    m_Box_General.pack_start(m_Button_Save, false, true);
    m_Box_General.pack_start(m_Button_StartStop, false, true);
    m_Box_General.pack_start(m_Button_Step, false, true);

    m_Box_FoodInfo.pack_start(m_Label_FoodInfo, false, true);
    m_Box_FoodInfo.pack_start(m_Label_FoodInfoValue, false, true);

    m_Box_AnthInfo.pack_start(m_Label_AnthInfo, false, true);
    m_Box_AnthInfo.pack_start(m_Button_Previous, false, true);
    m_Box_AnthInfo.pack_start(m_Button_Next, false, true);
    m_Box_AnthInfo.pack_start(m_Label_AnthInfoValue, false, true);

    // Set the box borders
    m_box_command.set_border_width(10);


    // Connect the clicked signal of the button to their signal handler
    m_Button_Exit.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Exit));
    m_Button_Open.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Open));
    m_Button_Save.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Save));
    m_Button_StartStop.signal_clicked().connect(
            sigc::mem_fun(*this,&Gui::on_button_clicked_StartStop));
    m_Button_Step.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Step));
    m_Button_Previous.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Previous));
    m_Button_Next.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::on_button_clicked_Next));

    // Show all children of the window
    show_all_children();
}

Gui::~Gui()
{
}

int Gui::window(shared_ptr<Simulation> simulation) {
    auto app = Gtk::Application::create("org.gtkmm.example");

    Gui gui(simulation);
    gui.set_title("TCHANZ 296190_331471");
    gui.set_default_size(820, 350);

    gui.show();

    return app->run(gui);
}