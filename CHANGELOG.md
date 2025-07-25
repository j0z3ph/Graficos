# Historial de cambios

Los cambios principales hechos al proyecto se escribiran aqui.

## [0.3.3] - 2025-07-25

### Corregido

- [C/C++] Se corrige un problema con las coordenadas de la funcion `circulo` y `circuloRelleno`.

## [0.3.2] - 2025-07-10

### Corregido

- [C/C++] Se corrige un error en las funciones de dibujo de figuras con relleno. Antes se dibujaban las figuras con relleno color blanco. Ahora se dibujan las figuras con relleno de color de la brocha actual.
- [C/C++] Se corrige un error en el render de imagenes de fondo que provocaba que algunas veces no se mostrara la imagen de fondo. 
- [C/C++] Se cambio el metodo de escalado para mejorar la calidad.
- [C/C++] Se corrigio una fuga de memoria en el metodo de creacion de nuevos HDC.

## [0.3.0] - 2025-01-18

### Cambiado
- [C/C++] Se cambio el nombre de la biblioteca a `graficos.h`, `graficos.hpp`, `graficos.c`, `graficos.cpp`.
- [C/C++] Se refactorizo el codigo para tratar de tener un mejor orden y claridad.
- [C/C++] Se agrego la funcion `imprimeEnConsola` la cual permite escribir mensajes en una terminal. Especialmente util para depuracion de codigo.
- [C/C++] Debido a la refactorizacion, el codigo anterior ya no es compatible con la version actual.

## [0.2.3] - 2024-07-08

### Corregido

- [C/C++] Se corrige un error en la funcion `color_fondo` y `color_fondo_rgb` que generaba un parpadeo en la pantalla.
- [C/C++] Se corrige un error en la funcion `muestraImagen` que hacia que las imagenes con mascara desaparecieran despues de un tiempo en ejecucion.
- [C/C++] Se corrige un error en la funcion `muestraImagen` que no liberaba correctamente memoria en el caso de las imagenes sin mascara.
- [C/C++] Se corrige un error en el manejo de las colas para los eventos keyDown y keyUp.
- [C] Se reescribe el manejo de las colas. Ya funciona.

### Cambiado

- [C/C++] Se cambia el orden del enumerador de teclas.
- [C] Se cambian las funciones `creaImagenBMP` y `creaImagenYMascaraBMP` para devolver un puntero. Los objetos creados por la funcion ahora estan en memoria dinamica.
- [C] Se cambia la funcion `eliminaImagen` para liberar la memoria dinamica creada por las funciones `creaImagenBMP` y `creaImagenYMascaraBMP`.
- [C] Se modifica el nombre de la estructura de imagenes. Ahora se llama `MiniWinImage`, igual que su contraparte en C++.


## [0.2.2] - 2024-05-01

### Agregado

- Nueva funcion `void fullscreen(bool fullscreenOn)`. Permite cambiar a modo pantalla completa o quitar el modo pantalla completa.
- Se agrega archivo de prueba `test.c` y `test.cpp`.

### Cambiado
 
- La funcion `vventana` se renombra a `ventana`.
- La funcion `vcierra` se renombra a `cierra`.
- La funcion `vtitulo` de renombra a `titulo`.
- El titulo por defecto de la ventana ahora es MiniWin [version].
- Se agrega nombre a los enumeradores de teclas y colores.
- Las funciones `color` y `color_fondo` ahora aceptan Colores (enumerador).
- Las funciones `color_fondo` y `color_fondo_rgb` actualizan la ventana para mostrar el cambio de color de fondo inmediatamente. 
- La ventana que se crea ya no permite maximizarla ni cambiar su tamaño con el raton.
- Ahora la ventana se coloca en el centro de la pantalla cuanto se crea o se redimensiona con las funciones `ventana` y `vredimensiona`.
- Se actualiza el archivo `MakeFile`.

### Corregido

- [C] Se cambia la funcion `muestraImagen` a paso de parametros por referencia tal como su contraparte en C++.
- [C] Se cambia la funcion `eliminaImagen` a paso de parametros por referencia.


## [0.2.1] - 2024-04-30

### Corregido

- [C++] Se corrige la funcion raton. Esperaba punteros, debia esperar referencias.

## [0.2.0] - 2024-04-21

### Agregado

- Se crea README.md y CHANGELOG.md.
- Se agrega version en C++.
- [C++] Clase MiniWinImage para cargar imagenes.
- [C] Estructura MiniWinImage para cargar imagenes.
- Funcion que permite crear una imagen.
- Funcion que permite eliminar una imagen.
- Funcion que permite mostrar una imagen en la ventana.
- Funcion que permite mostrar texto con tamano, estilo y tipo de letra personalizado.
- Funcion que permite detectar cuando una tecla se presiona y se suelta.


## [0.1.0] - 2023-12-09

### Agregado

- Traduccion a C.
- Funcion que permite cambiar el titulo de la ventana.
- Documentacion

### Cambiado

- Validacion de rangos en funciones de cambio de color.

