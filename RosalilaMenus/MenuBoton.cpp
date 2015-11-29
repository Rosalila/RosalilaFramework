#include "MenuBoton.h"

MenuBoton::MenuBoton(RosalilaGraphics*painter,int x, int y, int width, int height,
          Image* imagen,int alineacion_texto_x,int alineacion_texto_y, std::string texto,
          Image* imagen_sel,int alineacion_texto_x_sel,int alineacion_texto_y_sel, std::string texto_sel,
          std::string accion,string load_menu
          )
{
    this->x=x;
    this->y=y;
    this->height=height;
    this->width=width;
    this->imagen=imagen;
    this->texto=texto;
    this->alineacion_texto_x=alineacion_texto_x;
    this->alineacion_texto_y=alineacion_texto_y;
    this->imagen_sel=imagen_sel;
    this->texto_sel=texto_sel;
    this->alineacion_texto_x_sel=alineacion_texto_x_sel;
    this->alineacion_texto_y_sel=alineacion_texto_y_sel;
    this->seleccionado=false;
    this->accion=accion;
    this->load_menu=load_menu;
    this->painter=painter;
    this->input_config="not set";
}

std::string MenuBoton::getAccion()
{
    return accion;
}

std::string MenuBoton::getTipo()
{
    return "Boton";
}

void MenuBoton::dibujar()
{
    if(!seleccionado)
    {
        painter->draw2DImage
        (   imagen,
            width,height,
            x,y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());

        std::string temp=texto;
        painter->drawText(temp,x+alineacion_texto_x,y+alineacion_texto_y);
    }else
    {
        painter->draw2DImage
        (   imagen_sel,
            width,height,
            x,y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());

        std::string temp=texto_sel;
        painter->drawText(temp,x+alineacion_texto_x_sel,y+alineacion_texto_y_sel);
    }
}

bool MenuBoton::estaSeleccionado()
{
    return seleccionado;
}

void MenuBoton::setSeleccionado(bool seleccionado)
{
    this->seleccionado=seleccionado;
}
