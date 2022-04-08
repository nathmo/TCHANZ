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

using namespace std;

static Frame default_frame = {-(g_max*resolution/2), (g_max*resolution/2),
                              -(g_max*resolution/2), (g_max*resolution/2),
                              1, taille_dessin, taille_dessin};

Graphic::Graphic()
{
    setFrame(default_frame);
}

Graphic::~Graphic()
{
}

void Graphic::setFrame(Frame f)
{
    if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
    {
        f.asp = f.width/f.height;
        frame = f;
    }
    else
        std::cout << "incorrect Model framing or window parameters" << std::endl;
}

void Graphic::adjustFrame()
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    frame.width  = width;
    frame.height = height;

    // Preventing distorsion by adjusting the frame (cadrage)
    // to have the same proportion as the graphical area

    // use the reference framing as a Graphicde for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
        frame.yMax = default_frame.yMax ;
        frame.yMin = default_frame.yMin ;

        double delta(default_frame.xMax - default_frame.xMin);
        double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
        frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
        frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
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
                                  Frame frame)
{
    // déplace l'origine au centre de la fenêtre
    cr->translate(frame.width/2, frame.height/2);

    // normalise la largeur et hauteur aux valeurs fournies par le cadrage
    // ET inverse la direction de l'axe Y
    cr->scale(frame.width/(frame.xMax - frame.xMin),
              -frame.height/(frame.yMax - frame.yMin));

    // décalage au centre du cadrage
    cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

bool Graphic::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    // adjust the frame (cadrage) to prevent distortion when changing the window size
    adjustFrame();
    Graphic::orthographic_projection(cr, frame);

    //redraw the grid
    Graphic::drawFullGrid(cr);

    return true;
}

void Graphic::drawFullGrid(const Cairo::RefPtr<Cairo::Context>& cr){
    bool isBorder = false;
    for(int x=0;x<g_max;x++){
        for(int y=0;y<g_max;y++){
            if((x == 0)or(x == (g_max-1))or(y == 0)or(y == (g_max-1))){
                isBorder = true;
            } else {
                isBorder = false;
            }
            Graphic::drawEmptyCell(x,y,isBorder, cr);
        }
    }
}

void Graphic::drawEmptyCell(int x,int y,bool isBorder,
                            const Cairo::RefPtr<Cairo::Context>& cr){
    const int widthpx = resolution;
    x = x-(g_max/2);
    y = y-(g_max/2);
    // set background to black (or white if border)
    if(isBorder){
        cr->set_source_rgb(1, 1, 1);
    } else {
        cr->set_source_rgb(0, 0, 0);
    }
    cr->set_line_width(widthpx);
    cr->move_to(x*widthpx, y*widthpx+widthpx/2);
    cr->line_to((x+1)*widthpx,y*widthpx+widthpx/2);
    cr->stroke();
    // draw white box
    cr->set_source_rgb(1, 1, 1);
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
}
