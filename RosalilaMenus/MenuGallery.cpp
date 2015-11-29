#include "MenuGallery.h"

MenuGallery::MenuGallery(RosalilaGraphics*painter,int x, int y,
                   int size_x,int size_y,
                   int size_cuadro_x,int size_cuadro_y,
                   int separacion_x,int separacion_y,
                   int preview_pa_x,int preview_pa_y,
                   int image_amount,
                   int select_p1_x,int select_p1_y
                   )
{
    this->x=x;
    this->y=y;
    this->painter=painter;

    this->size_x=size_x;
    this->size_y=size_y;
    this->size_cuadro_x=size_cuadro_x;
    this->size_cuadro_y=size_cuadro_y;

    this->separacion_x=separacion_x;
    this->separacion_y=separacion_y;

    this->preview_pa_x=preview_pa_x;
    this->preview_pa_y=preview_pa_y;

    for(int i=0;i<image_amount;i++)
    {
        Image* thumbnail_temp=painter->getTexture(std::string("menu/gallery/thumbnails/")+toString(i+1)+std::string(".png"));
        Image* preview_temp=painter->getTexture(std::string("menu/gallery/previews/")+toString(i+1)+std::string(".png"));
        Image* fullscreen_temp=painter->getTexture(std::string("menu/gallery/fullscreen/")+toString(i+1)+std::string(".png"));

        portraits.push_back(thumbnail_temp);
        previews.push_back(preview_temp);
        fullscreens.push_back(fullscreen_temp);
    }

    this->select_p1_x=select_p1_x;
    this->select_p1_y=select_p1_y;

    border_cursor=painter->getTexture("menu/gallery/border_cursor.png");
    border_thumbnail=painter->getTexture("menu/gallery/border_thumbnail.png");
    border_preview=painter->getTexture("menu/gallery/border_preview.png");
    no_portrait=painter->getTexture("menu/gallery/no_image.png");
    filter=painter->getTexture("menu/gallery/filter.png");

    this->fullscreen_on=false;
    this->current_preview_alpha=0;
}

std::string MenuGallery::getTipo()
{
    return "Gallery";
}

void MenuGallery::dibujar()
{

    int cont=0;

    for(int j=0;j<size_y;j++)
        for(int i=0;i<size_x;i++)
        {
            //draw portraits
            if(cont<(int)portraits.size())
            {
                //draw preview pa
                if(select_p1_x+select_p1_y*size_x==cont)
                {
                    Image *image=previews[cont];
                    painter->draw2DImage
                    (   image,
                        image->getWidth(),image->getHeight(),
                        preview_pa_x,preview_pa_y,
                        1.0,
                        0.0,
                        false,
                        0,0,
                        Color(255,255,255,255),
                        0,0,
                        false,
                        FlatShadow());

                    int border_difference_x=(image->getWidth()-border_preview->getWidth())/2;
                    int border_difference_y=(image->getHeight()-border_preview->getHeight())/2;

                    painter->draw2DImage
                    (   border_preview,
                        border_preview->getWidth(),border_preview->getHeight(),
                        preview_pa_x+border_difference_x,preview_pa_y+border_difference_y,
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
            cont++;
        }
    cont=0;
    int position_selected=-1;
    for(int j=0;j<size_y;j++)
        for(int i=0;i<size_x;i++)
        {
            //dibujar portraits
            if(cont>=(int)portraits.size())
            {
                Image *image=no_portrait;
                painter->draw2DImage
                (   image,
                    size_cuadro_x,size_cuadro_y,
                    x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y),
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    0,0,
                    false,
                    FlatShadow());

                int border_difference_x=(size_cuadro_x-border_thumbnail->getWidth())/2;
                int border_difference_y=(size_cuadro_y-border_thumbnail->getHeight())/2;

                painter->draw2DImage
                (   border_thumbnail,
                    border_thumbnail->getWidth(),border_thumbnail->getHeight(),
                    x+i*(size_cuadro_x+separacion_x)+border_difference_x,y+j*(size_cuadro_y+separacion_y)+border_difference_y,
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    0,0,
                    false,
                    FlatShadow());
            }else
            {
                Image *image=portraits[cont];
                painter->draw2DImage
                (   image,
                    size_cuadro_x,size_cuadro_y,
                    x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y),
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    0,0,
                    false,
                    FlatShadow());

                int border_difference_x=(size_cuadro_x-border_thumbnail->getWidth())/2;
                int border_difference_y=(size_cuadro_y-border_thumbnail->getHeight())/2;

                painter->draw2DImage
                (   border_thumbnail,
                    border_thumbnail->getWidth(),border_thumbnail->getHeight(),
                    x+i*(size_cuadro_x+separacion_x)+border_difference_x,y+j*(size_cuadro_y+separacion_y)+border_difference_y,
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    0,0,
                    false,
                    FlatShadow());
            }

            //dibjujar cursor PA
            if(select_p1_x==i&&select_p1_y==j)
            {
                int border_difference_x=(size_cuadro_x-border_cursor->getWidth())/2;
                int border_difference_y=(size_cuadro_y-border_cursor->getHeight())/2;

                painter->draw2DImage
                (   border_cursor,
                    border_cursor->getWidth(),border_cursor->getHeight(),
                    x+i*(size_cuadro_x+separacion_x)+border_difference_x,y+j*(size_cuadro_y+separacion_y)+border_difference_y,
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    0,0,
                    false,
                    FlatShadow());
                position_selected=cont;
            }
            cont++;
        }
    if(fullscreen_on && position_selected!=-1 && position_selected<(int)fullscreens.size())//fullscreen
    {
        painter->draw2DImage
        (   filter,
            painter->screen_width,painter->screen_height,
            0,0,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,255),
            0,0,
            false,
            FlatShadow());

        Image *fullscreen_image=fullscreens[position_selected];
        int screen_difference_x=(painter->screen_width-fullscreen_image->getWidth())/2;
        int screen_difference_y=(painter->screen_height-fullscreen_image->getHeight())/2;
        painter->draw2DImage
        (   fullscreen_image,
            fullscreen_image->getWidth(),fullscreen_image->getHeight(),
            screen_difference_x,screen_difference_y,
            1.0,
            0.0,
            false,
            0,0,
            Color(255,255,255,current_preview_alpha),
            0,0,
            false,
            FlatShadow());
        current_preview_alpha+=3;
        if(current_preview_alpha>255)
            current_preview_alpha=255;
    }
}

void MenuGallery::select()
{
    fullscreen_on=true;
    current_preview_alpha=0;
}
