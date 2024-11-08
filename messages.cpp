#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdio>

//Mensajes generales
const char* fileOpenError = "\nError de validación o al abrir el archivo\n";

//Mensajes para la validacion de inicio de sesion y acciones en login.cpp
const char* loggedSuccessfully = "\nSe inició sesión de manera exitosa\n";
const char* nLoggedSuccessfully = "\nHubo un error al iniciar sesión\n";

const char* signInSuccessfully = "\nEl registro se realizó con éxito\n";
const char* nSignInSuccessfully = "\nNo se pudo realizar el registro\n";

//Para listar elementos
void listar(const char* elements){
    printf("\nLista de %s\n", elements);
}
//Operación para abrir archivos
FILE* openFileR(const char* filename) {
    FILE* file = fopen(filename, "rb");  // Open binary file
    if (file == NULL) {
        printf("%s",fileOpenError);
        return NULL;  // Return NULL to indicate failure
    }
    return file;  // Return the file pointer on success
}

FILE* openFileA(const char* filename) {
    FILE* file = fopen(filename, "ab");  // Open binary file
    if (file == NULL) {
        printf("%s",fileOpenError);
        return NULL;  // Return NULL to indicate failure
    }
    return file;  // Return the file pointer on success
}


#endif