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
#include <vector>

constexpr unsigned taille_dessin(512);

struct Frame {// Model Framing and window parameters
    double xMin; // frame parameters
    double xMax;
    double yMin;
    double yMax;
    double asp;  // frame aspect ratio
    int height;  // window height
    int width;   // window width
};

class Graphic : public Gtk::DrawingArea {
private:
    Frame frame;
    static std::vector<std::vector<double>> bufferLine;
    void emptyBuffer(const Cairo::RefPtr<Cairo::Context>& cr);

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
    static void drawLine(double xStart, double yStart,
                                  double xStop, double yStop,
                                  double largeur, int colorCode );
    static void color(double &r, double &g, double &b, int colorCode);
};

#endif //TCHANZ_GRAPHIC_H