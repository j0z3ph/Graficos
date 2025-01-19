# Graficos (antes MiniWin)
Biblioteca de funciones que permite dibujar en pantalla, detectar teclas y mouse, escribir texto y cargar imagenes. Basada en el proyecto [MiniWin de Pau Fernández](https://github.com/pauek/MiniWin).

La idea principal de este proyecto es tener una forma simple de creacion de mini juegos, que ayuden al estudiante a enfocarse en el desarrollo de su logica. 

# Uso

Por el momento, esta version de Graficos solo es compatible con Microsoft Windows. 

Para usar la biblioteca, solo hay que incluirla en nuestro codigo fuente.

## Compilacion

Para compilar en C:
 ```
gcc tu_codigo.c graficos.c -mwindows
 ```

Para compilar en C++:
 ```
g++ tu_codigo.cpp graficos.cpp -mwindows
 ```

De cualquier forma, se incluye un [Makefile](C/Makefile) para C y otro [Makefile](C++/Makefile) para C++ como ejemplos para cada una de las versiones.