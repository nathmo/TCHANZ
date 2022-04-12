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
    if( new_aspect_ratio > default_frame.asp) {//keep yMax/yMin. Adjust xMax/xMin
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
    vector<vector<double>> drawCommandList = Squarecell::FullGrid();
    for(auto drawCommand:drawCommandList) {
        Graphic::drawLine(drawCommand[0], drawCommand[1], drawCommand[2],
                          drawCommand[3], drawCommand[4], drawCommand[5], cr);
    }
    // add the entity
    for(auto entity:(*simulationPtr).getListEntity()) {
        // vector storing drawings parameters
        vector<vector<double>> drawCommandList = (*entity).draw(); //tableau contenant xStart, yStart, xStop, yStop, largeur, couleur
        for(auto drawCommand:drawCommandList) {
            Graphic::drawLine(drawCommand[0],drawCommand[1], drawCommand[2],
                              drawCommand[3],drawCommand[4], drawCommand[5], cr);
        }
    }
    return true;
}

void Graphic::drawLine(double xStart, double yStart, double xStop, double yStop, double largeur, int colorCode, const Cairo::RefPtr<Cairo::Context>& cr){
    double r = 0;
    double g = 0;
    double b = 0;
    Graphic::color(r,g,b, colorCode);
    cr->save();
    cr->set_line_width(largeur*resolution);
    cr->set_source_rgb(r, g, b);
    cr->move_to(xStart*resolution-g_max*resolution/2+resolution,
                yStart*resolution-g_max*resolution/2+resolution);
    cr->line_to(xStop*resolution-g_max*resolution/2+resolution,
                yStop*resolution-g_max*resolution/2+resolution);
    cr->stroke();
    cr->restore();
}

void Graphic::color(double &r, double &g, double &b, int colorCode) {
    vector<vector<double>> colorTable ={{1,0,0},                 //0 red
                                        {0,1,0},                 //1 green
                                        {0.3,0.3,1},             //2 bleu
                                        {1,1,0},                 //3 jaune
                                        {1,0.11,0.81},           //4 magenta
                                        {0,1,1},                 //5 cyan
                                        {1,0.5,0.5},             //6 light red
                                        {0.5,1,0.5},             //7 light green
                                        {0.5,0.6,1},             //8 light blue
                                        {0.81,0.81,0},           //9 light yellow
                                        {0.92,0.5,1},            //10 light magenta
                                        {0.6,1,1},               //11 light cyan
                                        {1,1,1},                 //12 white
                                        {0.7,0.7,0.7},           //13 grey
                                        {0,0,0}};                //14 black
    r=colorTable[colorCode][0];
    g=colorTable[colorCode][1];
    b=colorTable[colorCode][2];
}