#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "structs.h"
#include "messages.h"

void saveAndDisplayUser(FILE* file, const user& foundUser) {
    fwrite(&foundUser, sizeof(user), 1, file);
    printf("ID: %d\nNombre: %s %s\nCorreo: %s\nBloqueado: %s\nDeuda: %d\n\n",
           foundUser.id, foundUser.name, foundUser.lname, foundUser.mail,
           foundUser.blocked ? "Sí" : "No", foundUser.owed);
}

void searchUserById(int id) {
    FILE* file = openFileR("usuarios.dat");
    FILE* searchFile = openFileW("search.dat");
    if (!file || !searchFile) return;

    user currentUser;
    bool found = false;
    printf("\n--- Búsqueda por ID ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == id) {
            saveAndDisplayUser(searchFile, currentUser);
            found = true;
        }
    }
    if (!found) printf("No se encontró un usuario con ID: %d\n", id);

    fclose(file);
    fclose(searchFile);
}

void searchUserByName(const char* name) {
    FILE* file = openFileR("usuarios.dat");
    FILE* searchFile = openFileW("search.dat");
    if (!file || !searchFile) return;

    user currentUser;
    bool found = false;
    printf("\n--- Búsqueda por Nombre ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (strcmp(currentUser.name, name) == 0) {
            saveAndDisplayUser(searchFile, currentUser);
            found = true;
        }
    }
    if (!found) printf("No se encontró un usuario con el nombre: %s\n", name);

    fclose(file);
    fclose(searchFile);
}

void searchUserByLName(const char* lname) {
    FILE* file = openFileR("usuarios.dat");
    FILE* searchFile = openFileW("search.dat");
    if (!file || !searchFile) return;

    user currentUser;
    bool found = false;
    printf("\n--- Búsqueda por Apellido ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (strcmp(currentUser.lname, lname) == 0) {
            saveAndDisplayUser(searchFile, currentUser);
            found = true;
        }
    }
    if (!found) printf("No se encontró un usuario con el apellido: %s\n", lname);

    fclose(file);
    fclose(searchFile);
}

void searchUser(){
    char search[40];

    int i = atoi(search);

    searchUserById(i);
    searchUserByName(search);
    searchUserByLName(search);
}

void searchBook(const char* filename);

void searchBookById(const char* filename);

void searchBookByTitle(const char* filename);

void searchBookByAuthor(const char* filename);

void searchBookByGenre(const char* filename);

void searchBookByPYear(const char* filename);