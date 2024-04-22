/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include "miniwin.h"
#define GRAVITY 1
#define ANCHO 800
#define ALTO 600
#define JUMP -20

int main()
{
    int t, aceleracion = 0;
    bool i_presionada = false;
    bool d_presionada = false;
    float x = 150, y = 150;
    MWImage hongo = creaImagenYMascaraBMP(".\\hongoNoMask.bmp", ".\\hongomask.bmp");
    //MWImage hongo = creaImagenBMP(".\\hongo.bmp");
    hongo.pos_x = 150;
    hongo.pos_y = 150;

    hongo.alto = 50;
    hongo.ancho = 50;

    vventana(ANCHO, ALTO);
    vtitulo("Mi Primer Juego");

    color_fondo(ROJO);

    t = tecla();
    while (t != ESCAPE)
    {

        y += aceleracion;
        aceleracion += GRAVITY;
        if (y + hongo.alto > ALTO)
            y = ALTO - hongo.alto;
        if (i_presionada)
            x -= 10;
        if (x < 0)
            x = 0;
        if (d_presionada)
            x += 10;
        if (x + hongo.ancho > ANCHO)
            x = ANCHO - hongo.ancho;

        borra();
        color(NEGRO);
        // texto(20,20,"Presione ESC para salir");
        textoExt(20, 20, "Presione ESC para salir", 50, true, true, true, "Arial");
        texto(50, 150, "Hola");

        // color(VERDE);
        // rectangulo_lleno(x,y,x+50,y+50);
        hongo.pos_x = x;
        hongo.pos_y = y;

        // Imagen TEST
        muestraImagen(hongo);

        refresca();
        t = teclaDown();

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
    vcierra();
    return 0;
}
