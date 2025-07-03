# Library-CP2
Este proyecto consiste en crear un sistema de biblioteca en C que permitirá gestionar usuarios, libros y préstamos. Habrá dos tipos de personas: administradores (bibliotecarios) y usuarios (clientes). 

1. Funciones del Sistema
Administradores:

Ver la lista de usuarios y los libros que cada uno ha prestado.
Consultar si los libros están disponibles o prestados.
Cambiar el estado de los libros según los préstamos y devoluciones.
Cobrar una multa a usuarios que no devuelvan los libros a tiempo.
Bloquear usuarios hasta que devuelvan los libros atrasados y paguen lo que deben.
Agregar o eliminar libros del inventario de la biblioteca.

Usuarios:

Pueden buscar libros y ver si están disponibles.
Prestar hasta 2 libros al mismo tiempo.
Si se retrasa la devolución de un libro, tendrán que pagar una multa por cada libro atrasado para desbloquearse.

2. Reglas del Sistema

Los usuarios que no devuelvan un libro a tiempo quedarán bloqueados hasta que:
Devuelvan los libros atrasados.
Los administradores podrán desbloquear manualmente a los usuarios si lo consideran necesario.


4. Estructura del Proyecto
El sistema usará archivos para guardar la información, como:

usuarios.txt: Información de los usuarios y su estado (activo o bloqueado).
libros.txt: Lista de libros y su estado (disponible o prestado).

4. Objetivo del Proyecto
El objetivo es crear un sistema sencillo que permita gestionar una biblioteca y practicar la manipulación de archivos en C. También se pondrán en práctica conceptos como manejo de fechas, control de usuarios y gestión de multas.


