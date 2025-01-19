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
    Imagen *hongo = creaImagenConMascara("hongoNoMask.bmp", "hongomask.bmp");
    // MWImage hongo = creaImagenBMP("hongo.bmp");
    Imagen *fondo = creaImagen("fondo.bmp");
    if (hongo == NULL || fondo == NULL)
    {
        imprimeEnConsola("Imagenes no validas :(");
        return 0;
    }

    tamanioVentana(800, 600);
    tituloVentana("Mi Primer Juego");

    colorFondoRGB(200, 190, 210);

    t = teclaPresionada();
    while (t != TECLAS.ESCAPE)
    {
        y += aceleracion;
        aceleracion += GRAVITY;
        if (y + altoImagen(hongo) > altoVentana())
            y = altoVentana() - altoImagen(hongo);
        if (i_presionada)
            x -= 10;
        if (x < 0)
            x = 0;
        if (d_presionada)
            x += 10;
        if (x + anchoImagen(hongo) > anchoVentana())
            x = anchoVentana() - anchoImagen(hongo);

        limpiaVentana();
        muestraImagenEscalada(0, 0, anchoVentana(), altoVentana(), fondo);
        color(COLORES.ROJO);
        // texto(20,20,"Presione ESC para salir");
        texto2(20, 20, "Presione ESC para salir", 50, "Arial", true, true, true);
        texto(50, 150, "Hola");

        // Imagen TEST
        muestraImagen(x, y, hongo);

        actualizaVentana();
        t = teclaPresionada();

        if (t == TECLAS.ENTER)
        {
            on = !on;
            pantallaCompleta(on);
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

        t = teclaSoltada();
        if (t == TECLAS.IZQUIERDA)
        {
            i_presionada = false;
        }
        if (t == TECLAS.DERECHA)
        {
            d_presionada = false;
        }

        sprintf(msj, "X=%i, Y=%i\n", x, y);
        imprimeEnConsola(msj);

        espera(1000 / 120);
    }
    eliminaImagen(hongo);
    eliminaImagen(fondo);
    cierraVentana();

    return 0;
}
