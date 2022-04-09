/*!
  \file   gui.h
  \author Nathann Morand (90%) et Felipe Ramirez (10%)
  \date   MARS 2022
  \brief  prototype du module "gui".
*/

#ifndef TCHANZ_GUI_H
#define TCHANZ_GUI_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>
#include "graphic.h"
#include "simulation.h"

constexpr long msPerFrame(20);

class Gui : public Gtk::Window
{
private:
    Frame frame;
    std::shared_ptr<Simulation> simulationPtr;
protected:
    //Signal handlers:
    void on_button_clicked_Exit();
    void on_button_clicked_Open();
    void on_button_clicked_Save();
    void on_button_clicked_StartStop();
    void on_button_clicked_Step();
    bool on_tick();
    void on_button_clicked_Previous();
    void on_button_clicked_Next();
    void refreshSimulation();

    //Child widgets:
    Graphic graphic;
    Gtk::Box m_box_Gui, m_box_command, m_Box_General, m_Box_FoodInfo, m_Box_AnthInfo;
    Gtk::Separator m_Separator1;
    Gtk::Separator m_Separator2;
    Gtk::Label  m_Label_General;
    Gtk::Label  m_Label_FoodInfo;
    Gtk::Label  m_Label_FoodInfoValue;
    Gtk::Label  m_Label_AnthInfo;
    Gtk::Label m_Label_AnthInfoValue;
    Gtk::Button m_Button_Exit;
    Gtk::Button m_Button_Open;
    Gtk::Button m_Button_Save;
    Gtk::Button m_Button_StartStop;
    Gtk::Button m_Button_Step;
    Gtk::Button m_Button_Previous;
    Gtk::Button m_Button_Next;
public:
    Gui(std::shared_ptr<Simulation> simulation);
    virtual ~Gui();
    static int window(std::shared_ptr<Simulation> simulation);
};
#endif //TCHANZ_GUI_H
