#include "MenuTexto.h"

MenuTexto::MenuTexto(RosalilaGraphics*painter,int x, int y, std::string texto)
{
    this->x=x;
    this->y=y;
    this->height=-1;
    this->width=-1;
    this->texto=texto;
    this->painter=painter;
}

std::string MenuTexto::getTipo()
{
    return "Texto";
}

void MenuTexto::dibujar()
{
    painter->drawText(texto,x,y);
}
