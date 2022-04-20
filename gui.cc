/*!
  \file   gui.cc
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  implementation du module "gui".
*/

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <iostream>
#include "gui.h"
#include "graphic.h"
#include "simulation.h"

using namespace std;


void Gui::onButtonClickedExit() {
    hide(); //to close the application.
}

void Gui::onButtonClickedOpen() {
    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    int result = dialog.run();
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            (*simulationPtr).setPath(dialog.get_filename());
            (*simulationPtr).loadFromFile();
            Gui::refreshAnthInfo();
            Gui::refreshFoodInfo();
            (*simulationPtr).refreshGUI();
            graphic.queue_draw();//trigger refresh
            break;
        }
        default:
        {
            break;
        }
    }
}

void Gui::onButtonClickedSave() {
    Gtk::FileChooserDialog dialog("Please choose a file",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    int result = dialog.run();
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            (*simulationPtr).setPath(dialog.get_filename());
            (*simulationPtr).saveToFile();
            break;
        }
        default:
        {
            break;
        }
    }
}

void Gui::onButtonClickedStartStop() {
    if(m_Button_StartStop.get_label()=="start") {
        m_Button_Step.set_sensitive(false);
        m_Button_StartStop.set_label("stop");
    } else if (m_Button_StartStop.get_label()=="stop") {
        m_Button_Step.set_sensitive(true);
        m_Button_StartStop.set_label("start");
    }
}

void Gui::onButtonClickedStep() {
    if(m_Button_StartStop.get_label()=="start") { // step only if not actively simulating
        Gui::onTick();
    }
}

bool Gui::onTick() {
    if(m_Button_StartStop.get_label()=="stop") { // step only if actively simulating
        timer++;
        cout << "tick : "+to_string(timer) << endl;
        Gui::refreshAnthInfo();
        Gui::refreshFoodInfo();
        (*simulationPtr).simulateStep();
        graphic.queue_draw();//trigger refresh
    }
    return true;
}

void Gui::onButtonClickedPrevious() {
    if(idAnthillSelected==-1) {
        idAnthillSelected=(*simulationPtr).getAnthNb()-1;
    } else {
        idAnthillSelected--;
    }
    Gui::refreshAnthInfo();
}

void Gui::onButtonClickedNext() {
    if(idAnthillSelected==(*simulationPtr).getAnthNb()-1) {
        idAnthillSelected=-1;
    } else {
        idAnthillSelected++;
    }
    Gui::refreshAnthInfo();
}

bool Gui::on_key_press_event(GdkEventKey* event) {
    if((event->type == GDK_KEY_PRESS)&&(gdk_keyval_to_unicode(event->keyval) == 's')){
        Gui::onButtonClickedStartStop();
        return true;
    }
    if((event->type == GDK_KEY_PRESS)&&(gdk_keyval_to_unicode(event->keyval) == '1')){
        Gui::onButtonClickedStep();
        return true;
    }
    if((event->type == GDK_KEY_PRESS)&&(gdk_keyval_to_unicode(event->keyval) == 'n')){
        Gui::onButtonClickedNext();
        return true;
    }
    if((event->type == GDK_KEY_PRESS)&&(gdk_keyval_to_unicode(event->keyval) == 'p')){
        Gui::onButtonClickedPrevious();
        return true;
    }
    if((event->type == GDK_KEY_PRESS)&&(gdk_keyval_to_unicode(event->keyval) == 'q')){
        Gui::onButtonClickedExit();
        return true;
    }
    return false;
}

void Gui::refreshFoodInfo() {
    string nbFood = to_string((*simulationPtr).getFoodNb());
    m_Label_FoodInfoValue.set_text("Nb food: "+nbFood);
}
void Gui::refreshAnthInfo() {


    if(idAnthillSelected >= (*simulationPtr).getAnthNb()) {
        idAnthillSelected =(*simulationPtr).getAnthNb()-1;
    }
    if(idAnthillSelected == -1) {
        string statToDisplay = "None selected";
        m_Label_AnthInfoValue.set_text(statToDisplay);
    } else {
        vector<int> stat = (*simulationPtr).getAnthInfoStat(idAnthillSelected);
        string statToDisplay = "id: "+to_string(idAnthillSelected)+"\n"+
                "Total food: "+to_string(stat[0])+"\n"+"\n"+
                "nbC: "+to_string(stat[1])+"\n"+
                "nbD: "+to_string(stat[2])+"\n"+
                "nbP: "+to_string(stat[3])+"\n";
        m_Label_AnthInfoValue.set_text(statToDisplay);
    }
}

Gui::Gui(shared_ptr<Simulation> simulation) :
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
        m_Button_Next("next") {

    simulationPtr = simulation;
    // Set title and border of the window
    set_title("layout buttons");
    set_border_width(0);
    // Add outer box to the window (the window can only contain a single widget)
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
    m_box_command.set_border_width(10);// Set the box borders
    // Connect the clicked signal of the button to their signal handler
    m_Button_Exit.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedExit));
    m_Button_Open.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedOpen));
    m_Button_Save.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedSave));
    m_Button_StartStop.signal_clicked().connect(
            sigc::mem_fun(*this,&Gui::onButtonClickedStartStop));
    m_Button_Step.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedStep));
    m_Button_Previous.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedPrevious));
    m_Button_Next.signal_clicked().connect(
            sigc::mem_fun(*this, &Gui::onButtonClickedNext));
    add_events(Gdk::KEY_RELEASE_MASK);
    //create the timer
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &Gui::onTick), msPerFrame);
    show_all_children();// Show all children of the window
    Gui::refreshAnthInfo();
    Gui::refreshFoodInfo();
    (*simulationPtr).refreshGUI();
    //graphic.queue_draw();//trigger refresh
}

Gui::~Gui() {
}

int Gui::window(shared_ptr<Simulation> simulation) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    Gui gui(simulation);
    gui.set_title("TCHANZ 296190_331471");
    gui.set_default_size(1000, 800);
    gui.show();
    return app->run(gui);
}