#ifndef MENUBOTON_H
#define MENUBOTON_H

#include "Elemento.h"

class MenuBoton:Elemento
{
private:
    bool seleccionado;
    std::string accion;
    Image* imagen;
    int alineacion_texto_x,alineacion_texto_y;
    Image* imagen_sel;
    int alineacion_texto_x_sel,alineacion_texto_y_sel;
    //otra
public:
    char* load_menu;
    std::string texto;
    std::string texto_sel;
    std::string input_config;
    MenuBoton(RosalilaGraphics*painter,int x, int y, int width, int height,
              Image* imagen,int alineacion_texto_x,int alineacion_texto_y, std::string texto,
              Image* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, std::string texto_sel,
              std::string accion,char* load_menu
              );
    std::string getAccion();
    virtual std::string getTipo();
    virtual void dibujar();
    bool estaSeleccionado();
    void setSeleccionado(bool seleccionado);
};

#endif
