#ifndef MENUCONTENEDOR_H
#define MENUCONTENEDOR_H

#include "RosalilaMenus/Elemento.h"
#include "RosalilaMenus/MenuLista.h"
#include "RosalilaMenus/MenuBarra.h"
#include "RosalilaMenus/MenuBoton.h"
#include "RosalilaMenus/MenuImagen.h"
#include "RosalilaMenus/MenuTexto.h"

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
