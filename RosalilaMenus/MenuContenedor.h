#ifndef MENUCONTENEDOR_H
#define MENUCONTENEDOR_H

#include "Elemento.h"
#include "MenuLista.h"
#include "MenuBarra.h"
#include "MenuBoton.h"
#include "MenuImagen.h"
#include "MenuTexto.h"

class MenuContenedor:Elemento
{
private:
    int seleccionado;
public:
    std::vector<Elemento*> elementos;
    MenuContenedor(RosalilaGraphics*painter,std::vector<Elemento*> elementos);
    virtual std::string getTipo();
    virtual void dibujar();
    void avanzar();
    void retroceder();
    Elemento* getElementoSeleccionado();
};

#endif
