#ifndef MENUTEXTO_H
#define MENUTEXTO_H

#include "Elemento.h"

class MenuTexto:Elemento
{
public:
    std::string texto;
    MenuTexto(RosalilaGraphics*painter,int x, int y,std::string texto);
    virtual std::string getTipo();
    virtual void dibujar();
};

#endif
