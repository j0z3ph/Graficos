# Historial de cambios

Los cambios principales hechos al proyecto se escribiran aqui.

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

