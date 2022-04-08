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

using namespace std;

int Gui::window() {
    auto app = Gtk::Application::create("org.gtkmm.example");

    Gui gui;
    gui.set_title("TCHANZ 296190_331471");
    gui.set_default_size(820, 350);

    gui.show();

    return app->run(gui);
}


Gui::Gui() :
        graphic(),
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
    // Set title and border of the window
    set_title("layout buttons");
    set_border_width(0);

    // Add outer box to the window (because the window
    // can only contain a single widget)
    add(m_box_Gui);

    //Put the inner boxes and the separator in the outer box:
    m_box_Gui.pack_start(m_box_command);
    m_box_Gui.pack_start(graphic);

    m_box_command.pack_start(m_Box_General);
    m_box_command.pack_start(m_Box_FoodInfo);
    m_box_command.pack_start(m_Box_AnthInfo);

    m_Box_General.pack_start(m_Label_General);
    m_Box_General.pack_start(m_Button_Exit);
    m_Box_General.pack_start(m_Button_Open);
    m_Box_General.pack_start(m_Button_Save);
    m_Box_General.pack_start(m_Button_StartStop);
    m_Box_General.pack_start(m_Button_Step);

    m_Box_FoodInfo.pack_start(m_Label_FoodInfo);
    m_Box_FoodInfo.pack_start(m_Label_FoodInfoValue);

    m_Box_AnthInfo.pack_start(m_Label_AnthInfo);
    m_Box_AnthInfo.pack_start(m_Button_Previous);
    m_Box_AnthInfo.pack_start(m_Button_Next);
    m_Box_AnthInfo.pack_start(m_Label_AnthInfoValue);

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

void Gui::on_button_clicked_Exit(){
    hide(); //to close the application.
}
void Gui::on_button_clicked_Open(){
    cout << "open" << endl;
}
void Gui::on_button_clicked_Save(){
    cout << "save" << endl;
}
void Gui::on_button_clicked_StartStop(){
    cout << "start" << endl;
}
void Gui::on_button_clicked_Step(){
    cout << "step" << endl;
}
void Gui::on_button_clicked_Previous(){
    cout << "previous" << endl;
}
void Gui::on_button_clicked_Next(){
    cout << "next" << endl;
}
