/*!
  \file   graphic.h
  \author Nathann Morand (30%) et Felipe Ramirez (70%)
  \date   MARS 2022
  \brief  prototype du module "graphic".
*/

#ifndef TCHANZ_GRAPHIC_H
#define TCHANZ_GRAPHIC_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/frame.h>

constexpr unsigned taille_dessin(500);

struct Frame // Model Framing and window parameters
{
    double xMin; // frame parameters
    double xMax;
    double yMin;
    double yMax;
    double asp;  // frame aspect ratio
    int height;  // window height
    int width;   // window width
};

class Graphic : public Gtk::DrawingArea
{
private:
    Frame frame;
protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
public:
    Graphic();
    virtual ~Graphic();
    void setFrame(Frame f);
    void adjustFrame();
    static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr,
                                        Frame frame);
    static void drawFullGrid(const Cairo::RefPtr<Cairo::Context>& cr);
    static void drawEmptyCell(int x, int y, bool isBorder,
                       const Cairo::RefPtr<Cairo::Context>& cr);
};

#endif //TCHANZ_GRAPHIC_H