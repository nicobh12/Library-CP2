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
        case FICTION: return "Fiction";
        case NON_FICTION: return "Non-Fiction";
        case MYSTERY: return "Mystery";
        case FANTASY: return "Fantasy";
        case SCIENCE_FICTION: return "Science Fiction";
        case BIOGRAPHY: return "Biography";
        case HISTORY: return "History";
        case POETRY: return "Poetry";
        case YOUNG_ADULT: return "Young Adult";
        case OTHER: return "Other";
        default: return "Unknown";  // This handles any out-of-range values (e.g., if there's a bug)
    }
}


#endif