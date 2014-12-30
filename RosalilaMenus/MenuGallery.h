#ifndef MENUGALLERY_H
#define MENUGALLERY_H

#include <vector>
#include "Elemento.h"


class MenuGallery:Elemento
{
private:
    int size_cuadro_x,size_cuadro_y;
    int separacion_x,separacion_y;
    int preview_pa_x,preview_pa_y;
    int current_preview_alpha;
    std::vector<Image*>portraits;
    std::vector<Image*>previews;
    std::vector<Image*>fullscreens;
    Image* border_cursor;
    Image* border_thumbnail;
    Image* border_preview;
    Image* no_portrait;
    Image* filter;
public:
    bool fullscreen_on;
    int select_p1_x,select_p1_y;
    int size_x,size_y;
    MenuGallery(RosalilaGraphics*painter,int x, int y,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int  separacion_y,
                   int preview_pa_x,int preview_pa_y,
                   int image_amount,
                   int select_p1_x,int select_p1_y
                   );
    virtual std::string getTipo();
    virtual void dibujar();
    void select();
};

#endif
