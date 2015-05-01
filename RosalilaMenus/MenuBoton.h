#ifndef MENUBOTON_H
#define MENUBOTON_H

#include "Elemento.h"

class MenuBoton:Elemento
{
private:
    bool seleccionado;
    std::string accion;
    Image* imagen;
    Image* imagen_sel;
    int alineacion_texto_x_sel,alineacion_texto_y_sel;
    //otra
public:
    string load_menu;
    std::string texto;
    std::string texto_sel;
    std::string input_config;
    int alineacion_texto_x,alineacion_texto_y;
    MenuBoton(RosalilaGraphics*painter,int x, int y, int width, int height,
              Image* imagen,int alineacion_texto_x,int alineacion_texto_y, std::string texto,
              Image* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, std::string texto_sel,
              std::string accion,string load_menu
              );
    std::string getAccion();
    virtual std::string getTipo();
    virtual void dibujar();
    bool estaSeleccionado();
    void setSeleccionado(bool seleccionado);
};

#endif
