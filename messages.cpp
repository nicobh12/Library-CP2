#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdio>
#include "structs.h"
#include <locale.h>


//Mensajes generales
const char* fileOpenError = "\nError de validacion o al abrir el archivo\n";

//Mensajes para la validacion de inicio de sesion y acciones en login.cpp
const char* loggedSuccessfully = "\nSInicio de sesion exitoso\n";
const char* nLoggedSuccessfully = "\nHubo un error al iniciar sesion\n";

const char* signInSuccessfully = "\nEl registro fue realizado con exito\n";
const char* nSignInSuccessfully = "\nNo se pudo realizar el registro\n";

//Mensajes para otras acciones
const char* userNotFound = "\nUsuario no encontrado\n";
const char* userBlocked = "\nUsuario bloqueado\n";
const char* userUnblocked = "\nUsuario desbloqueado\n";
const char* feePaid = "\nSe ha pagado la deuda\n";
const char* noFeeToPay = "\nEl usuario no tiene una deuda activa\n";
const char* feeAssigned = "\nDeuda asignada exitosamente\n";
const char* dataChanged = "\nDatos actualizados exitosamente\n";
const char* bookAddedSuccessfully = "\nLibro agregado correctamente\n";
const char* alreadyTwoBooksBorrowed = "\nTransaccion excede el limite de prestamos\n";
const char* bookNotAvailable = "\nLibro no disponible\n";
const char* bookBorrowedSuccessfully = "\nLibro prestado exitosamente";
const char* bookNotFound = "\nLibro no encontrado";
const char* bookDeletedSuccessfully = "\nLibro eliminado exitosamente\n";
const char* bookModifiedSuccessfully = "\nLibro modificado exitosamente\n";
const char* userDeletedSuccessfully = "\nUsuario eliminado exitosamente\n";
const char* adminDeletedSuccessfully = "\nAdministrador eliminado correctamente\n";
const char* adminNotFound = "\nAdministrador no encontrado\n";
const char* usersSortedSuccessfully = "\neUsuarios ordenados correctamente";
const char* adminsSortedSuccessfully = "\nAdministradores ordenados correctamente";
const char* booksSortedSuccessfully = "\nLibros ordenados correctamente";
const char* genreNotFound = "\nGenero no encontrado\n";
const char* noBooksInGenre = "\nNo hay libros del genero buscado\n";


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

FILE* openFileRPlus(const char* filename) {
    FILE* file = fopen(filename, "r+b");  // Open binary file
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

FILE* openFileW(const char* filename) {
    FILE* file = fopen(filename, "wb");  // Open binary file
    if (file == NULL) {
        printf("%s",fileOpenError);
        return NULL;  // Return NULL to indicate failure
    }
    return file;  // Return the file pointer on success
}


const char* genreToString(genre g) {
    switch (g) {
        case FICCION: return "Ficcion";
        case NO_FICCION: return "No Ficcion";
        case MISTERIO: return "Misterio";
        case FANTASIA: return "Fantasia";
        case CIENCIA_FICCION: return "Ciencia Ficcion";
        case BIOGRAFIA: return "Biografia";
        case HISTORIA: return "Historia";
        case POESIA: return "Poesia";
        case YOUNG_ADULT: return "Young Adult";  // Lo dejo igual, ya que "Young Adult" es comúnmente usado en español también
        case OTRO: return "Otro";
        default: return "Desconocido";  // En caso de valores fuera de rango
    }
}

#endif