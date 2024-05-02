#include"miniwin.hpp"

using namespace miniwin;

int main()
{
    int t;
    float x,y;
    bool full = false;
    ventana(300,300);
    color_fondo(Colores::BLANCO);

    t = tecla();
    while(t != Teclas::ESCAPE) {
        t = tecla();
        if(t == Teclas::ESPACIO) {
            full= !full;
            fullscreen(full);
        }
        borra();

        raton(x,y);
        color(Colores::AZUL);
        circulo(x,y,10);

        refresca();

        espera(1);
    }
    
    cierra();
    return 0;
}

