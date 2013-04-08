#include "RosalilaMenus/MenuGallery.h"

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

        portraits.push_back(thumbnail_temp);
        previews.push_back(preview_temp);
    }

    this->select_p1_x=select_p1_x;
    this->select_p1_y=select_p1_y;

    border_cursor=painter->getTexture("menu/gallery/border_cursor.png");
    border_thumbnail=painter->getTexture("menu/gallery/border_thumbnail.png");
    border_preview=painter->getTexture("menu/gallery/border_preview.png");
    no_portrait=painter->getTexture("menu/gallery/no_image.png");
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
                        false);

                    painter->draw2DImage
                    (   border_preview,
                        border_preview->getWidth(),border_preview->getHeight(),
                        preview_pa_x,preview_pa_y,
                        1.0,
                        0.0,
                        false,
                        0,0,
                        Color(255,255,255,255),
                        false);
                }
            }
            cont++;
        }
    cont=0;
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
                    false);
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
                    false);
            }
            //dibjujar cursor PA
            if(select_p1_x==i&&select_p1_y==j)
            {
                Image*image=border_cursor;
                painter->draw2DImage
                (   image,
                    size_cuadro_x,size_cuadro_y,
                    x+i*(size_cuadro_x+separacion_x),y+j*(size_cuadro_y+separacion_y),
                    1.0,
                    0.0,
                    false,
                    0,0,
                    Color(255,255,255,255),
                    false);
            }
            cont++;
        }
}
