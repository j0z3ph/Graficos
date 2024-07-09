#include <stdio.h>
#include "miniwin.h"
#define GRAVITY 1
#define JUMP -20

int main()
{
    int t, aceleracion = 0;
    bool on = false;
    bool i_presionada = false;
    bool d_presionada = false;
    float x = 150, y = 150;
    MWImage *hongo = creaImagenYMascaraBMP("hongoNoMask.bmp", "hongomask.bmp");
    //MWImage hongo = creaImagenBMP("hongo.bmp");
    MWImage *fondo = creaImagenBMP("fondo.bmp");
    hongo->pos_x = 150;
    hongo->pos_y = 150;

    //hongo.alto = 50;
    //hongo.ancho = 50;

    ventana(800, 600);
    titulo("Mi Primer Juego");

    color_fondo(ROJO);

    t = tecla();
    while (t != ESCAPE)
    {
        y += aceleracion;
        aceleracion += GRAVITY;
        if (y + hongo->alto > valto())
            y = valto() - hongo->alto;
        if (i_presionada)
            x -= 10;
        if (x < 0)
            x = 0;
        if (d_presionada)
            x += 10;
        if (x + hongo->ancho > vancho())
            x = vancho() - hongo->ancho;

        borra();
        muestraImagen(fondo);
        color(NEGRO);
        // texto(20,20,"Presione ESC para salir");
        textoExt(20, 20, "Presione ESC para salir", 50, true, true, true, "Arial");
        texto(50, 150, "Hola");

        // color(VERDE);
        // rectangulo_lleno(x,y,x+50,y+50);
        hongo->pos_x = x;
        hongo->pos_y = y;

        // Imagen TEST
        muestraImagen(hongo);

        refresca();
        t = teclaDown();

        if(t == RETURN) {
            on = !on;
            fullscreen(on);
        }

        if (t == IZQUIERDA)
        {
            i_presionada = true;
        }
        if (t == DERECHA)
        {
            d_presionada = true;
        }
        if (t == ESPACIO)
        {
            aceleracion = JUMP;
        }

        t = teclaUp();
        if (t == IZQUIERDA)
        {
            i_presionada = false;
        }
        if (t == DERECHA)
        {
            d_presionada = false;
        }

        espera(1);
    }
    eliminaImagen(hongo);
    eliminaImagen(fondo);
    cierra();
    return 0;
}
