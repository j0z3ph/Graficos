/**
 * @file graficos.hpp
 * @author Jose Luis Cruz (j0z3ph@gmail.com)
 * @brief Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presión de algunas teclas. Básicamente para hacer
 *    juegos sencillos.
 *    Basado en el trabajo de Pau Fernández.
 * @version 0.2.2
 * @date 2023-12-09
 *
 *  MiniWin: Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presión de algunas teclas. Básicamente para hacer
 *    juegos sencillos.
 *
 *  (c) Pau Fernández, licencia MIT: http://es.wikipedia.org/wiki/MIT_License
 *
 * Git original: https://github.com/pauek/MiniWin
 * Git: https://github.com/j0z3ph/Miniwin
 */

#ifndef _GRAFICOS_HPP_
#define _GRAFICOS_HPP_

#define _GRAFICOS_VERSION_ "Graficos 0.3.3"

#include <iostream>
#include <windows.h>

#ifndef _GRAFICOS_SOURCE_
#define main _main_ // Super-cutre hack! (pero funciona)
#endif

int _main_();

namespace graficos
{

    /// @brief Listado de teclas conocidas
    extern const struct Teclas
    {
        int ESCAPE;
        int IZQUIERDA;
        int DERECHA;
        int ARRIBA;
        int ABAJO;
        int F1;
        int F2;
        int F3;
        int F4;
        int F5;
        int F6;
        int F7;
        int F8;
        int F9;
        int F10;
        int ESPACIO;
        int ENTER;
        int NUMERO_0;
        int NUMERO_1;
        int NUMERO_2;
        int NUMERO_3;
        int NUMERO_4;
        int NUMERO_5;
        int NUMERO_6;
        int NUMERO_7;
        int NUMERO_8;
        int NUMERO_9;
        int LETRA_A;
        int LETRA_B;
        int LETRA_C;
        int LETRA_D;
        int LETRA_E;
        int LETRA_F;
        int LETRA_G;
        int LETRA_H;
        int LETRA_I;
        int LETRA_J;
        int LETRA_K;
        int LETRA_L;
        int LETRA_M;
        int LETRA_N;
        int LETRA_O;
        int LETRA_P;
        int LETRA_Q;
        int LETRA_R;
        int LETRA_S;
        int LETRA_T;
        int LETRA_U;
        int LETRA_V;
        int LETRA_W;
        int LETRA_X;
        int LETRA_Y;
        int LETRA_Z;
        int NINGUNA;
    } TECLAS;

    /// @brief Listado de colores basicos
    extern const struct Colores
    {
        int NEGRO;
        int ROJO;
        int VERDE;
        int AZUL;
        int AMARILLO;
        int MAGENTA;
        int CYAN;
        int BLANCO;
    } COLORES;

    class Imagen
    {
    private:
        int _ancho;
        int _alto;
        HGDIOBJ _hBitmap;
        HGDIOBJ _hBitmapMask;
        HDC _hdcimg;
        HDC _hdcimg_mask;
        friend void _renderImage(int x, int y, int w, int h, graficos::Imagen &imagen);

    public:
        /**
         * @brief Crea una imagen de MiniWin
         *
         * @param ruta La ruta de la imagen. El archivo debe ser <b>BMP</b>
         */
        Imagen(std::string ruta);
        /**
         * @brief Crea una imagen de MiniWin
         *
         * @param ruta La ruta de la imagen. El archivo debe ser <b>BMP</b>
         * @param ruta_mask La ruta de la mascara. El archivo debe ser <b>BMP</b> y del mismo tamanio
         * que la imagen.
         */
        Imagen(std::string ruta, std::string ruta_mask);

        ~Imagen();

        /**
         * @brief Obtiene el ancho en pixeles de la imagen.
         *
         * @return long Ancho.
         */
        int ancho();
        /**
         * @brief Obtiene el alto en pixeles de la imagen.
         *
         * @return long Alto.
         */
        int alto();
    };

    class GraficosAPI
    {
    public:
        /**
         * @brief Imprime un mensaje en la consola.
         * @note Este metodo abre una nueva terminal.
         *
         * @param msj El mensaje que se desea imprimir
         */
        void imprimeEnConsola(const std::string &msj);

        /**
         * @brief Permite cambiar al modo pantalla completa.
         * @note Las dimensiones de la ventana cambian.
         *
         * @param fs Si es true, cambia al modo pantalla completa.
         * Si es false, regresa al modo ventana con las ultimas dimensiones establecidas.
         */
        void pantallaCompleta(bool fs);

        /**
         * @brief Permite cambiar el color de fondo de la ventana.
         *
         * @param c Nuevo color de alguno de los enumeradores.
         */
        void colorFondo(int c);

        /**
         * @brief Permite cambiar el color de fondo de la ventana.
         *
         * @param r Rojo (0-255)
         * @param g Verde (0-255)
         * @param b Azul (0-255)
         */
        void colorFondo(UINT8 r, UINT8 g, UINT8 b);

        /**
         * @brief Muestra una imagen en pantalla en las
         * coordenadas especificadas.
         *
         * @param x Coordenada en X
         * @param y Coordenada en Y
         * @param imagen Imagen a mostrar
         */
        void muestraImagen(int x, int y, Imagen &imagen);
        /**
         * @brief Muestra una imagen en pantalla en las
         * coordenadas especificadas.
         *
         * @param x Coordenada en X
         * @param y Coordenada en Y
         * @param imagen Imagen a mostrar
         */
        void muestraImagen(int x, int y, Imagen *imagen);

        /**
         * @brief Muestra una imagen en pamtalla en las
         * coordenadas y el tamaño especificados.
         *
         * @param x Coordenada en X
         * @param y Coordenada en Y
         * @param ancho Ancho de la imagen
         * @param alto Alto de la Imagen
         * @param imagen Imagen a mostrar
         */
        void muestraImagen(int x, int y, int ancho, int alto, Imagen &imagen);
        /**
         * @brief Muestra una imagen en pamtalla en las
         * coordenadas y el tamaño especificados.
         *
         * @param x Coordenada en X
         * @param y Coordenada en Y
         * @param ancho Ancho de la imagen
         * @param alto Alto de la Imagen
         * @param imagen Imagen a mostrar
         */
        void muestraImagen(int x, int y, int ancho, int alto, Imagen *imagen);

        /**
         * @brief Permite imprimir un texto en pantalla.
         *
         * @param x Posicion en X
         * @param y Posicion en Y
         * @param texto Texto a mostrar
         * @param tamanioFuente Tamanio de la fuente
         * @param fuente Nombre de la fuente a usar.
         * @param italica True para mostrar en italica. False para mostrar normal.
         * @param negrita True para mostrar en negrita. False para mostrar normal.
         * @param subrayada True para mostrar texto subrayado. False para mostrar normal.
         */
        void texto(int x, int y, const std::string &texto, int tamanioFuente, const std::string &fuente,
                   bool italica = false, bool negrita = false, bool subrayada = false);

        /**
         * @brief Permite determinar si se solto una tecla.
         *
         * @return Codigo de la tecla que se solto.
         */
        int teclaSoltada();
        /**
         * @brief Permite determinar si se presiono una tecla.
         *
         * @return Codigo de la tecla presionada.
         */
        int teclaPresionada();

        /**
         * @brief Limpia el contenido de la ventana.
         * El color del fondo de la ventana se manda al color del fondo.
         *
         */
        void limpiaVentana();
        /**
         * @brief Forza el repintado del contenido de la ventana.
         *
         */
        void actualizaVentana();
        /**
         * @brief Muestra un dialogo con el mensaje indicado.
         *
         * @param msj Mensaje que se mostrara en el dialogo.
         */
        void muestraMensaje(const std::string &msj);
        /**
         * @brief Muestra un dialogo con el mensaje indicado.
         *
         * @param msj Mensaje que se mostrara en el dialogo.
         * @param titulo Titulo del dialogo.
         */
        void muestraMensaje(const std::string &msj, const std::string &titulo);
        /**
         * @brief Muestra un dialogo de pregunta.
         *
         * @param msj Mensaje que se mostrara en el dialogo.
         * @return true Si la respuesta fue afirmativa.
         * @return false En cualquier otro caso.
         */
        bool muestraPregunta(const std::string &msj);
        /**
         * @brief Muestra un dialogo de pregunta.
         *
         * @param msj Mensaje que se mostrara en el dialogo.
         * @param titulo Titulo del dialogo.
         * @return true Si la respuesta fue afirmativa.
         * @return false En cualquier otro caso.
         */
        bool muestraPregunta(const std::string &msj, const std::string &titulo);
        /**
         * @brief Detiene la ejecucion del proceso por una cantidad
         * de tiempo.
         *
         * @param miliseg Tiempo en milisegundos que se detendra el proceso.
         */
        void espera(int miliseg);

        /**
         * @brief Obtiene el ancho de la ventana.
         *
         * @return int Ancho de la ventana.
         */
        int ancho();
        /**
         * @brief Obtiene el alto de la ventana.
         *
         * @return int Alto de la ventana.
         */
        int alto();
        /**
         * @brief Permite cambiar el tamanio de la ventana.
         *
         * @param ancho Nuevo ancho.
         * @param alto Nuevo alto.
         */
        void tamanio(int ancho, int alto);
        /**
         * @brief Permite cerrar la ventana.
         *
         */
        void cierra();
        /**
         * @brief Permite cambiar el titulo de la ventana.
         *
         * @param titulo Nuevo titulo de la ventana.
         */
        void titulo(const std::string &titulo);

        /**
         * @brief Permite cambiar el color a usar para dibujar en
         * la pantalla.
         *
         * @param c Entero entre 0 y 7
         *
         * 0 - NEGRO
         *
         * 1 - ROJO
         *
         * 2 - VERDE
         *
         * 3 - AZUL
         *
         * 4 - AMARILLO
         *
         * 5 - MAGENTA
         *
         * 6 - CYAN
         *
         * 7 - BLANCO
         */
        void color(int c);
        /**
         * @brief Permite cambiar el color a usar para dibujar en
         * la pantalla.
         *
         * @param r Cantidad de rojo (0-255)
         * @param g Cantidad de verde (0-255)
         * @param b Cantidad de azul (0-255)
         */
        void color(UINT8 r, UINT8 g, UINT8 b);

        /**
         * @brief Permite dibujar un punto en la ventana.
         *
         * @param x Coordenada x.
         * @param y Coordenada y.
         */
        void punto(int x, int y);
        /**
         * @brief Permite dibujar una linea en la pantalla.
         *
         * @param x1 Coordenada x inicial.
         * @param y1 Coordenada y inicial.
         * @param x2 Coordenada x final.
         * @param y2 Coordenada y final.
         */
        void linea(int x1, int y1, int x2, int y2);
        /**
         * @brief Permite dibujar un rectangulo sin relleno en la ventana.
         *
         * @param x1 Coordenada x de la esquina superior izquierda.
         * @param y1 Coordenada y de la esquina superior izquierda.
         * @param x2 Coordenada x de la esquina inferior derecha.
         * @param y2 Coordenada y de la esquina inferior derecha.
         */
        void rectangulo(int x1, int y1, int x2, int y2);
        /**
         * @brief Permite dibujar un rectangulo con relleno en la ventana.
         *
         * @param x1 Coordenada x de la esquina superior izquierda.
         * @param y1 Coordenada y de la esquina superior izquierda.
         * @param x2 Coordenada x de la esquina inferior derecha.
         * @param y2 Coordenada y de la esquina inferior derecha.
         */
        void rectanguloRelleno(int x1, int y1, int x2, int y2);
        /**
         * @brief Permite dibujar un circulo sin relleno en la ventana.
         *
         * @param x Coordenada x del centro del circulo.
         * @param y Coordenada y del centro del circulo.
         * @param radio Radio del circulo.
         */
        void circulo(int x, int y, int radio);
        /**
         * @brief Permite dibujar un circulo con relleno en la ventana.
         *
         * @param x Coordenada x del centro del circulo.
         * @param y Coordenada y del centro del circulo.
         * @param radio Radio del circulo.
         */
        void circuloRelleno(int x, int y, int radio);
        /**
         * @brief Permite dibujar un texto simple en la ventana.
         *
         * @param x Coordenada x.
         * @param y Coordenada y.
         * @param texto Texto a dibujar.
         */
        void texto(int x, int y, const std::string &texto);

        /**
         * @brief Permite obtener la posicion x,y del mouse
         * respecto a la ventana.
         *
         * @param x Posicion del raton en x.
         * @param y Posicion del raton en y.
         * @returns true Si el mouse se encuentra dentro de la ventana.
         * false Si el mouse se encuentra fuera de la ventana.
         */
        bool raton(int &x, int &y);
        /**
         * @brief Permite saber si el mouse se encuentra dentro de la ventana.
         *
         * @return true Si el mouse se encuentra dentro de la ventana.
         *
         * @return false Si el mouse se encuentra fuera de la ventana.
         */
        bool ratonEnVentana();
        /**
         * @brief Permite obtener la coordenada en x del raton.
         *
         * @return Coordenada en x.
         */
        int ratonX();
        /**
         * @brief Permite obtener la coordenada en y del raton.
         *
         * @return Coordenada en y.
         */
        int ratonY();
        /**
         * @brief Permite obtener el boton del mouse que se a presionado.
         *
         * @param izq true Si se presiono el boton izquierdo. false En cualquier otro caso.
         * @param der true Si se presiono el boton derecho. false En cualquier otro caso.
         */
        void ratonBotones(bool &izq, bool &der);
        /**
         * @brief Permite determinar si se presiono el boton izquierdo del mouse.
         *
         * @return true Si se presiono.
         * @return Si no se presiono.
         */
        bool ratonBotonIzquierdo();
        /**
         * @brief Permite determinar si se presiono el boton derecho del mouse.
         *
         * @return true Si se presiono.
         * @return false Si no se presiono.
         */
        bool ratonBotonDerecho();
    };

    /// @brief Objeto principal que representa la ventana
    extern GraficosAPI ventana;

    class GraficosException : public std::exception
    {
    private:
        std::string mensaje;

    public:
        GraficosException(const std::string &msg);

        const char *what() const throw();
    };

} // namespace graficos

#endif
