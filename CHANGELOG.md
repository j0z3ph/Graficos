# Historial de cambios

Los cambios principales hechos al proyecto se escribiran aqui.

## [0.2.3] - 2024-07-08

### Corregido

- [C/C++] Se corrige un error en la funcion `color_fondo` y `color_fondo_rgb` que generaba un parpadeo en la pantalla.
- [C/C++] Se corrige un error en la funcion `muestraImagen` que hacia que las imagenes con mascara desaparecieran despues de un tiempo en ejecucion.
- [C/C++] Se corrige un error en la funcion `muestraImagen` que no liberaba correctamente memoria en el caso de las imagenes sin mascara.

### Cambiado

- [C] Se cambian las funciones `creaImagenBMP` y `creaImagenYMascaraBMP` para devolver un puntero. Los objetos creados por la funcion ahora estan en memoria dinamica.
- [C] Se cambia la funcion `eliminaImagen` para liberar la memoria dinamica creada por las funciones `creaImagenBMP` y `creaImagenYMascaraBMP`.


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

