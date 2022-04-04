//
// Created by nathann on 04.04.22.
//

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "gui.h"

int Gui::window() {
    auto app = Gtk::Application::create("org.gtkmm.example");

    Gtk::Window win;
    win.set_title("TCHANZ");
    win.set_default_size(820, 350);

    //Logo logo;
    //win.add(logo);
    //logo.show();
    return app->run(win);
}