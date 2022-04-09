/*!
  \file   graphic.cc
  \author Nathann Morand (30%) et Felipe Ramirez (70%)
  \date   MARS 2022
  \brief  implementation du module "graphic".
*/

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <cairomm/context.h>
#include <iostream>
#include "graphic.h"
#include "constantes.h"
#include "simulation.h"

using namespace std;

static Frame default_frame = {-(g_max*resolution/2), (g_max*resolution/2),
                              -(g_max*resolution/2), (g_max*resolution/2),
                              1, taille_dessin, taille_dessin};

Graphic::Graphic(shared_ptr<Simulation> simulation) {
    setFrame(default_frame);
    this->simulationPtr = simulation;
}

Graphic::~Graphic() {
}

void Graphic::setFrame(Frame f) {
    if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0)) {
        f.asp = f.width/f.height;
        frame = f;
    } else
        std::cout << "incorrect Model framing or window parameters" << std::endl;
}

void Graphic::adjustFrame() {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    frame.width  = width;
    frame.height = height;

    // Preventing distorsion by adjusting the frame (cadrage)
    // to have the same proportion as the graphical area

    // use the reference framing as a Graphicde for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp) { // keep yMax and yMin. Adjust xMax and xMin
        frame.yMax = default_frame.yMax ;
        frame.yMin = default_frame.yMin ;

        double delta(default_frame.xMax - default_frame.xMin);
        double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
        frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
        frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
    } else { // keep xMax and xMin. Adjust yMax and yMin
        frame.xMax = default_frame.xMax ;
        frame.xMin = default_frame.xMin ;

        double delta(default_frame.yMax - default_frame.yMin);
        double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
        frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
        frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
    }
}

void Graphic::orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr,
                                  Frame frame) {
    // déplace l'origine au centre de la fenêtre
    cr->translate(frame.width/2, frame.height/2);

    // normalise la largeur et hauteur aux valeurs fournies par le cadrage
    // ET inverse la direction de l'axe Y
    cr->scale(frame.width/(frame.xMax - frame.xMin),
              -frame.height/(frame.yMax - frame.yMin));

    // décalage au centre du cadrage
    cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

bool Graphic::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // adjust the frame (cadrage) to prevent distortion when changing the window size
    adjustFrame();
    Graphic::orthographic_projection(cr, frame);
    //redraw the grid
    Graphic::drawFullGrid(cr);
    // add the entity
    for(auto entity:(*simulationPtr).getListEntity()){
        (*entity).draw(cr);
    }

    return true;
}

void Graphic::drawFullGrid(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->save();
    //white border
    cr->set_line_width(g_max*resolution);
    cr->set_source_rgb(1, 1, 1);
    cr->move_to(-g_max*resolution/2+1, 0);
    cr->line_to(g_max*resolution/2, 0);
    cr->stroke();
    // black bacground
    cr->set_line_width((g_max-2)*resolution);
    cr->set_source_rgb(0, 0, 0);
    cr->move_to(-g_max*resolution/2+1+resolution, 0);
    cr->line_to(g_max*resolution/2-resolution, 0);
    cr->stroke();
    // vertical line
    cr->set_source_rgb(0.8, 0.8, 0.8); // slight grey, better contrast with white item
    cr->set_line_width(1);
    for(int x=(1-g_max/2);x<g_max/2;x++){
        cr->move_to(x*resolution, -g_max*resolution/2+1);
        cr->line_to(x*resolution, g_max*resolution/2);
    }
    // horizonal line
    for(int y=(1-g_max/2);y<g_max/2;y++){
        cr->move_to(-g_max*resolution/2+1, y*resolution);
        cr->line_to(g_max*resolution/2,y*resolution);
    }
    cr->stroke();
    cr->restore();
}

void Graphic::color(double &R, double &G, double &B, int id, bool lightColor) {
    int indexColor = id%6;
    if(indexColor == 0) {
        if(lightColor == true) { //rouge
            R = 1;
            G = 0.30;
            B = 0.30;
        }
        R = 1;
        G = 0;
        B = 0;
    } else if(indexColor == 1) { //vert
        if(lightColor == true) {
            R = 0.50;
            G = 1;
            B = 0.50;
        }
        R = 0;
        G = 1;
        B = 0;
    } else if(indexColor == 2) { //bleu
        if(lightColor == true) {
            R = 0.30;
            G = 0.50;
            B = 1;
        }
        R = 0;
        G = 0;
        B = 1;
    } else if(indexColor == 3) { //jaune
        if(lightColor == true) {
            R = 0.92;
            G = 1;
            B = 0.5;
        }
        R = 1;
        G = 1;
        B = 0.2;
    } else if(indexColor == 4) { //magenta
        if(lightColor == true) {
            R = 0.88;
            G = 0.30;
            B = 1;
        }
        R = 1;
        G = 0.11;
        B = 0.81;
    } else if(indexColor == 5) { //cyan
        if(lightColor == true) {
            R = 0.40;
            G = 1;
            B = 1;
        }
        R = 0;
        G = 1;
        B = 1;
    }
}

void Graphic::drawSquare(int x, int y, int id, bool lightColor, const Cairo::RefPtr<Cairo::Context>& cr) {
    const int widthpx = resolution;
    x = x-(g_max/2);
    y = y-(g_max/2);
    cr->save();

    double R(0);
    double G(0);
    double B(0);

    color(R, G, B, id, lightColor); //probleme apparement peut pas appeler ??

    cr->set_source_rgb(R, G, B); // slight grey, better contrast with white item
    cr->set_line_width(1);
    cr->move_to(x*widthpx, y*widthpx);
    cr->line_to((x+1)*widthpx,y*widthpx);

    cr->move_to((x+1)*widthpx,y*widthpx);
    cr->line_to((x+1)*widthpx,(y+1)*widthpx);

    cr->move_to((x+1)*widthpx,(y+1)*widthpx);
    cr->line_to((x)*widthpx,(y+1)*widthpx);

    cr->move_to((x)*widthpx,(y+1)*widthpx);
    cr->line_to((x)*widthpx,(y)*widthpx);

    cr->stroke();
    cr->restore();
}


/*
int count(0);
if(specie == fourmiDefensorCST) {
count++;
}
if(specie == fourmiCollectorCST) continue; //savoir si on commence par foncé ou clair

for(int i(0); i < sizeSide; i++) {
if((count%2)==0) {

} else {

}
}
*/