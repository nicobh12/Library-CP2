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

void viewBorrows(bool isAdmin) {
    FILE* file = openFileR("books.dat");

    infoBooks currentBook;
    listar("libros no disponibles");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.available == 0) {
            printf("ID: %d\nTítulo: %s\nAutor: %s\nGénero: %d\nPrestados: %d\n\n",
                   currentBook.id, currentBook.b.title, currentBook.b.author, genreToString(currentBook.b.g), currentBook.total);

            // Si es administrador, muestra quiénes han prestado el libro
            if (isAdmin && currentBook.borrows != nullptr) {
                printf("Usuarios que prestaron el libro:\n");
                for (int i = 0; i < currentBook.total; i++) {
                    printf("ID Usuario: %d, Nombre: %s %s\n",
                           currentBook.borrows[i].id, currentBook.borrows[i].name, currentBook.borrows[i].lname);
                }
                printf("\n");
            }
        }
    }
}

void availableBooks(bool isAdmin) {
    FILE* file = openFileR("books.dat");

    infoBooks currentBook;
    listar("libros disponibles");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.available > 0) {
            printf("ID: %d\nTítulo: %s\nAutor: %s\nGénero: %d\nDisponibles: %d de %d\n\n",
                   currentBook.id, currentBook.b.title, currentBook.b.author, genreToString(currentBook.b.g),
                   currentBook.available, currentBook.total);

            // Si es administrador, muestra quiénes tienen el libro en préstamo
            if (isAdmin && currentBook.available != currentBook.total && currentBook.borrows != nullptr) {
                printf("Usuarios que tienen el libro en préstamo:\n");
                for (int i = 0; i < currentBook.total - currentBook.available; i++) {
                    printf("ID Usuario: %d, Nombre: %s %s\n",
                           currentBook.borrows[i].id, currentBook.borrows[i].name, currentBook.borrows[i].lname);
                }
                printf("\n");
            }
        }
    }
}

// Muestra todos los libros, incluyendo prestados y disponibles
void viewAllBooks(bool isAdmin) {

    listar("todos los libros");
    availableBooks(isAdmin);
    viewBorrows(isAdmin);
}

void viewAdmins(const char* filename);