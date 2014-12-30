#include "MenuContenedor.h"

MenuContenedor::MenuContenedor(RosalilaGraphics*painter,std::vector<Elemento*> elementos)
{
    this->x=-1;
    this->y=-1;
    this->height=-1;
    this->width=-1;
    this->elementos=elementos;
    this->seleccionado=0;
    for(int i=0;i<(int)elementos.size();i++)
        if(elementos[i]->getTipo()=="Boton" || elementos[i]->getTipo()=="Lista" || elementos[i]->getTipo()=="Barra")
        {
            if(elementos[i]->getTipo()=="Boton")
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Lista")
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Barra")
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
    this->painter=painter;
}

std::string MenuContenedor::getTipo()
{
    return "Contenedor";
}

void MenuContenedor::dibujar()
{
    for(int i=0;i<(int)elementos.size();i++)
        elementos[i]->dibujar();
}

void MenuContenedor::avanzar()
{
    for(int i=seleccionado+1;i<(int)elementos.size();i++)
        if(elementos[i]->getTipo()=="Boton" || elementos[i]->getTipo()=="Lista" || elementos[i]->getTipo()=="Barra")
        {
            if(elementos[seleccionado]->getTipo()=="Boton")
                ((MenuBoton*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()=="Lista")
                ((MenuLista*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()=="Barra")
                ((MenuBarra*)elementos[seleccionado])->setSeleccionado(false);

            if(elementos[i]->getTipo()=="Boton")
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Lista")
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Barra")
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
}

void MenuContenedor::retroceder()
{
    for(int i=seleccionado-1;i>=0;i--)
        if(elementos[i]->getTipo()=="Boton" || elementos[i]->getTipo()=="Lista" || elementos[i]->getTipo()=="Barra")
        {
            if(elementos[seleccionado]->getTipo()=="Boton")
                ((MenuBoton*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()=="Lista")
                ((MenuLista*)elementos[seleccionado])->setSeleccionado(false);
            if(elementos[seleccionado]->getTipo()=="Barra")
                ((MenuBarra*)elementos[seleccionado])->setSeleccionado(false);

            if(elementos[i]->getTipo()=="Boton")
                ((MenuBoton*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Lista")
                ((MenuLista*)elementos[i])->setSeleccionado(true);
            if(elementos[i]->getTipo()=="Barra")
                ((MenuBarra*)elementos[i])->setSeleccionado(true);
            seleccionado=i;
            break;
        }
}

Elemento* MenuContenedor::getElementoSeleccionado()
{
    return elementos[seleccionado];
}
