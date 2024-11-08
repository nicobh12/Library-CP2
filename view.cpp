#include "structs.h"
#include "messages.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>  

// Muestra solo los usuarios bloqueados
void viewBlockedUsers() {
    FILE* file = openFileR("usuarios.dat");

    user currentUser;

    listar("usuarios bloqueados");
    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.blocked) {
            printf("ID: %d\nNombre: %s %s\nCorreo: %s\nDeuda: %d\n\n",
                   currentUser.id, currentUser.name, currentUser.lname, currentUser.mail, currentUser.owed);
        }
    }

    fclose(file);
}

// Muestra solo los usuarios desbloqueados
void viewUnblockedUsers() {
    FILE* file = openFileR("usuarios.dat");

    user currentUser;
    listar("usuarios activos");
    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (!currentUser.blocked) {
            printf("ID: %d\nNombre: %s %s\nCorreo: %s\nDeuda: %d\n\n",
                   currentUser.id, currentUser.name, currentUser.lname, currentUser.mail, currentUser.owed);
        }
    }

    fclose(file);
}

void viewAllUsers() {
    listar("todos los usuarios registrados");
    viewUnblockedUsers();
    viewBlockedUsers();  
}


void viewAllBooks(const char* filename);

void viewBorrows(const char* filename);

void availableBooks(const char* filename);

void viewAdmins(const char* filename);