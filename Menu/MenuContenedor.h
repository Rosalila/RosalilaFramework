#ifndef MENUCONTENEDOR_H
#define MENUCONTENEDOR_H

#include "Menu/Elemento.h"
#include "Menu/MenuLista.h"
#include "Menu/MenuBarra.h"
#include "Menu/MenuBoton.h"
#include "Menu/MenuImagen.h"
#include "Menu/MenuTexto.h"

class MenuContenedor:Elemento
{
private:
    int seleccionado;
public:
    std::vector<Elemento*> elementos;
    MenuContenedor(Painter*painter,std::vector<Elemento*> elementos);
    virtual std::string getTipo();
    virtual void dibujar();
    void avanzar();
    void retroceder();
    Elemento* getElementoSeleccionado();
};

#endif
