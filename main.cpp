/*Biblioteca en C: Archivo principal. Información general en README.md
Con solo llamar a mainMenu, se puede ejecutar todo el programa
Realizado con compilador MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r1 14.2.0 */

#include <cstdio>
#include <cstdlib>
#include "messages.h"

int main(){

    int id = 0;
    bool admin = false;

    mainMenu(id, admin);

    return 0;
}