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
#include<stdio.h>
#include"miniwin.h"
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
    vventana(ANCHO,ALTO);
    vtitulo("Mi Primer Juego");

    t = tecla();
    while(t != ESCAPE) {

        y+= aceleracion;
        aceleracion += GRAVITY;
        if(y + 50 > ALTO) y = ALTO-50;
        if(i_presionada) x-=10;
        if(x < 0) x = 0;
        if(d_presionada) x+=10;
        if(x+50 > ANCHO) x = ANCHO - 50;

        borra();
        color(BLANCO);
        //texto(20,20,"Presione ESC para salir");
        textoExt(20,20,"Presione ESC para salir", 50, false, false, true, "Arial");
        texto(50,150, "Hola");


        color(VERDE);
        rectangulo_lleno(x,y,x+50,y+50);


        refresca();
        t = teclaDown();

        if(t == IZQUIERDA) {
            i_presionada = true;
        }
        if(t == DERECHA) {
            d_presionada = true;
        }
        if(t == ESPACIO) {
            aceleracion=JUMP;
        }

        t = teclaUp();
        if(t == IZQUIERDA) {
            i_presionada = false;
        }
        if(t == DERECHA) {
            d_presionada = false;
        }
        
        
        espera(1);
    }
    vcierra();
    return 0;
}
