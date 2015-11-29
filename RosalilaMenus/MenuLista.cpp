#include "MenuLista.h"

MenuLista::MenuLista(RosalilaGraphics*painter,int x, int y,
          int flecha_izq_x,int flecha_izq_y,Image*flecha_izquierda,int flecha_der_x,int flecha_der_y,Image*flecha_derecha,
          int flecha_izq_x_sel,int flecha_izq_y_sel,Image*flecha_izquierda_sel,int flecha_der_x_sel,int flecha_der_y_sel,Image*flecha_derecha_sel,
          std::vector<Elemento*>elementos,std::string accion
          )
{
    this->x=x;
    this->y=y;

    this->flecha_izq_x=flecha_izq_x;
    this->flecha_izq_y=flecha_izq_y;
    this->flecha_izquierda=flecha_izquierda;
    this->flecha_der_x=flecha_der_x;
    this->flecha_der_y=flecha_der_y;
    this->flecha_derecha=flecha_derecha;

    this->flecha_izq_x_sel=flecha_izq_x_sel;
    this->flecha_izq_y_sel=flecha_izq_y_sel;
    this->flecha_izquierda_sel=flecha_izquierda_sel;
    this->flecha_der_x_sel=flecha_der_x_sel;
    this->flecha_der_y_sel=flecha_der_y_sel;
    this->flecha_derecha_sel=flecha_derecha_sel;

    this->elementos=elementos;
    actual=0;
    this->accion=accion;
    seleccionado=false;
    this->painter=painter;
}

std::string MenuLista::getTipo()
{
    return "Lista";
}

void MenuLista::avanzar()
{
    actual++;
    if(actual>=(int)elementos.size())
        actual=(int)elementos.size()-1;
//    if(actual<(int)elementos.size()-1)
//        actual++;
}

void MenuLista::retroceder()
{
    actual--;
    if(actual<0)
        actual=0;
//    if(actual>0)
//        actual--;
}

void MenuLista::dibujar()
{
    if(!seleccionado)
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar();
        if(flecha_izquierda!=NULL)
        {
            painter->draw2DImage
            (   flecha_izquierda,
                width,height,
                x+flecha_izq_x,y+flecha_izq_y,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false,
                FlatShadow());
        }
        if(flecha_derecha!=NULL)
        {
            painter->draw2DImage
            (   flecha_derecha,
                width,height,
                x+flecha_der_x,y+flecha_der_y,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false,
                FlatShadow());
        }
    }else
    {
        if(actual>=0 && actual<(int)elementos.size())
            elementos[actual]->dibujar();
        if(flecha_izquierda_sel!=NULL)
        {
            painter->draw2DImage
            (   flecha_izquierda_sel,
                width,height,
                x+flecha_izq_x_sel,y+flecha_izq_y_sel,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false,
                FlatShadow());
        }
        if(flecha_derecha_sel!=NULL)
        {
            painter->draw2DImage
            (   flecha_derecha_sel,
                width,height,
                x+flecha_der_x_sel,y+flecha_der_y_sel,
                1.0,
                0.0,
                false,
                0,0,
                Color(255,255,255,255),
                0,0,
                false,
                FlatShadow());
        }
    }
}

bool MenuLista::estaSeleccionado()
{
    return seleccionado;
}

void MenuLista::setSeleccionado(bool seleccionado)
{
    this->seleccionado=seleccionado;
}

std::string MenuLista::getAccion()
{
    return accion;
}

Elemento* MenuLista::getElementoActual()
{
    return elementos[actual];
}
