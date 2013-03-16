#ifndef MENUTEXTO_H
#define MENUTEXTO_H

#include "Menu/Elemento.h"

class MenuTexto:Elemento
{
public:
    std::string texto;
    MenuTexto(Painter*painter,int x, int y,std::string texto);
    virtual std::string getTipo();
    virtual void dibujar();
};

#endif
