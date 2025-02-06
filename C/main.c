#include <stdio.h>
#include "graficos.h"
#define GRAVITY 1
#define JUMP -20

int main()
{
    int t, aceleracion = 0;
    bool on = false;
    bool i_presionada = false;
    bool d_presionada = false;
    int x = 150, y = 150;
    char msj[100];
    Imagen *hongo = ventana.creaImagenConMascara("hongoNoMask.bmp", "hongomask.bmp");
    // MWImage hongo = creaImagenBMP("hongo.bmp");
    Imagen *fondo = ventana.creaImagen("fondo.bmp");
    if (hongo == NULL || fondo == NULL)
    {
        ventana.imprimeEnConsola("Imagenes no validas :(");
        return 0;
    }

    ventana.tamanioVentana(800, 600);
    ventana.tituloVentana("Mi Primer Juego");

    ventana.colorFondoRGB(200, 190, 210);

    t = ventana.teclaPresionada();
    while (t != TECLAS.ESCAPE)
    {
        y += aceleracion;
        aceleracion += GRAVITY;
        if (y + ventana.altoImagen(hongo) > ventana.altoVentana())
            y = ventana.altoVentana() - ventana.altoImagen(hongo);
        if (i_presionada)
            x -= 10;
        if (x < 0)
            x = 0;
        if (d_presionada)
            x += 10;
        if (x + ventana.anchoImagen(hongo) > ventana.anchoVentana())
            x = ventana.anchoVentana() - ventana.anchoImagen(hongo);

            ventana.limpiaVentana();
            ventana.muestraImagenEscalada(0, 0, ventana.anchoVentana(), ventana.altoVentana(), fondo);
            ventana.color(COLORES.ROJO);
        // texto(20,20,"Presione ESC para salir");
        ventana.texto2(20, 20, "Presione ESC para salir", 50, "Arial", true, true, true);
        ventana.texto(50, 150, "Hola");

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

        sprintf(msj, "X=%i, Y=%i\n", x, y);
        ventana.imprimeEnConsola(msj);

        ventana.espera(1);
    }
    ventana.eliminaImagen(hongo);
    ventana.eliminaImagen(fondo);
    ventana.cierraVentana();

    return 0;
}
