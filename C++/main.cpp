/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <string>
#include "graficos.hpp"
#define GRAVITY 1
#define JUMP -20

using namespace std;
using namespace graficos;

int main()
{
    int t, aceleracion = 0;
    bool on = false;
    bool i_presionada = false;
    bool d_presionada = false;
    int x = 150, y = 150;
    Imagen *hongo;
    Imagen *fondo;
    try
    {
        hongo = new Imagen("hongo.bmp", "hongomask.bmp");
        fondo = new Imagen("fondo.bmp");
    }
    catch (const GraficosException &e)
    {
        ventana.imprimeEnConsola(e.what());
        return 1;
    }

    ventana.tamanio(800, 600);
    //ventana.titulo("Mi Primer Juego");

    ventana.colorFondo(COLORES.ROJO);

    t = ventana.teclaPresionada();
    while (t != TECLAS.ESCAPE)
    {
        y += aceleracion;
        aceleracion += GRAVITY;
        if (y + hongo->alto() > ventana.alto())
            y = ventana.alto() - hongo->alto();
        if (i_presionada)
            x -= 10;
        if (x < 0)
            x = 0;
        if (d_presionada)
            x += 10;
        if (x + hongo->ancho() > ventana.ancho())
            x = ventana.ancho() - hongo->ancho();

        ventana.limpiaVentana();
        //ventana.muestraImagen(0, 0, ventana.ancho(), ventana.alto(), fondo);
        ventana.muestraImagen(0, 0, fondo);
        ventana.color(COLORES.ROJO);
        ventana.texto(20, 20, "Presione ESC para salir", 50, "Arial", true, true, true);
        ventana.texto(50, 150, "Hola");

        ventana.color(COLORES.AZUL);
        ventana.rectanguloRelleno(100,150, 200, 250);
        // Imagen TEST
        ventana.muestraImagen(x, y, hongo);

        ventana.actualizaVentana();
        t = ventana.teclaPresionada();

        if (t == TECLAS.ENTER)
        {
            on = !on;
            ventana.pantallaCompleta(on);
        }

        if (t == TECLAS.IZQUIERDA)
        {
            i_presionada = true;
        }
        if (t == TECLAS.DERECHA)
        {
            d_presionada = true;
        }
        if (t == TECLAS.ESPACIO)
        {
            aceleracion = JUMP;
        }

        t = ventana.teclaSoltada();
        if (t == TECLAS.IZQUIERDA)
        {
            i_presionada = false;
        }
        if (t == TECLAS.DERECHA)
        {
            d_presionada = false;
        }

        //ventana.imprimeEnConsola("X=" + to_string(x) + ", Y=" + to_string(y) + "\n");
        ventana.espera(1);
    }

    ventana.cierra();
    return 0;
}
