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

class Gui : public Gtk::Window
{
private:
    Frame frame;
protected:
    //Signal handlers:
    void on_button_clicked_Hello();
    void on_button_clicked_Bonjour();
    void on_button_clicked_Monsieur();
    void on_button_clicked_Madame();
    void on_button_clicked_Fin();

    //Child widgets:
    Gtk::Box m_Box_Top, m_Box1, m_Box2;
    Gtk::Separator m_Separator1;
    Gtk::Separator m_Separator2;
    Gtk::Label  m_Label_Salutation;
    Gtk::Label  m_Label_Destinataire;
    Gtk::Label  m_Label_Fin;
    Gtk::Button m_Button_Hello;
    Gtk::Button m_Button_Bonjour;
    Gtk::Button m_Button_Monsieur;
    Gtk::Button m_Button_Madame;
    Gtk::Button m_Button_Fin;
public:
    Gui();
    virtual ~Gui();
    static int window();
};
#endif //TCHANZ_GUI_H
