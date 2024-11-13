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

void saveAndDisplayBook(FILE* file, const book& foundBook) {
    fwrite(&foundBook, sizeof(book), 1, file);
    printf("Título: %s\nAutor: %s\nGénero: %d\nAño de Publicación: %d\n\n",
           foundBook.title, foundBook.author, foundBook.g, foundBook.pYear);
}

void searchBookById(int id) {
    FILE* file = openFileR("books.dat");
    FILE* searchFile = openFileW("searchBooks.dat");
    if (!file || !searchFile) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Búsqueda por ID ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.id == id) {
            saveAndDisplayBook(searchFile, currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontró un libro con ID: %d\n", id);

    fclose(file);
    fclose(searchFile);
}

void searchBookByTitle(const char* title) {
    FILE* file = openFileR("books.dat");
    FILE* searchFile = openFileW("searchBooks.dat");
    if (!file || !searchFile) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Búsqueda por Título ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (strcmp(currentBook.b.title, title) == 0) {
            saveAndDisplayBook(searchFile, currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontró un libro con el título: %s\n", title);

    fclose(file);
    fclose(searchFile);
}

void searchBookByAuthor(const char* author) {
    FILE* file = openFileR("books.dat");
    FILE* searchFile = openFileW("searchBooks.dat");
    if (!file || !searchFile) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Búsqueda por Autor ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (strcmp(currentBook.b.author, author) == 0) {
            saveAndDisplayBook(searchFile, currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontró un libro del autor: %s\n", author);

    fclose(file);
    fclose(searchFile);
}

void searchByGenre(const char* g) {
    genre searchGenre;

    if (strcasecmp(g, "FICCION") == 0) searchGenre = FICCION;
    else if (strcasecmp(g, "NO_FICCION") == 0) searchGenre = NO_FICCION;
    else if (strcasecmp(g, "MISTERIO") == 0) searchGenre = MISTERIO;
    else if (strcasecmp(g, "FANTASIA") == 0) searchGenre = FANTASIA;
    else if (strcasecmp(g, "CIENCIA_FICCION") == 0) searchGenre = CIENCIA_FICCION;
    else if (strcasecmp(g, "BIOGRAFIA") == 0) searchGenre = BIOGRAFIA;
    else if (strcasecmp(g, "HISTORIA") == 0) searchGenre = HISTORIA;
    else if (strcasecmp(g, "POESIA") == 0) searchGenre = POESIA;
    else if (strcasecmp(g, "YOUNG_ADULT") == 0) searchGenre = YOUNG_ADULT;
    else if (strcasecmp(g, "OTRO") == 0) searchGenre = OTRO;
    else {
        printf("%s", genreNotFound);
        return;
    }

    FILE *file = openFileR("libros.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;

    printf("Libros encontrados en el género %s:\n", g);
    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.b.g == searchGenre) {
            printf("Título: %s\nAutor: %s\nAño de Publicación: %d\n\n", currentBook.b.title, currentBook.b.author, currentBook.b.pYear);
            found = true;
        }
    }

    if (!found) printf("%s", noBooksInGenre);
    fclose(file);
}

void searchBookByPYear(int year) {
    FILE* file = openFileR("books.dat");
    FILE* searchFile = openFileW("searchBooks.dat");
    if (!file || !searchFile) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Búsqueda por Año de Publicación ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.b.pYear == year) {
            saveAndDisplayBook(searchFile, currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontró un libro publicado en el año: %d\n", year);

    fclose(file);
    fclose(searchFile);
}

void searchBook(){
    char search[50];

    int p = atoi(search);

    searchBookById(p);
    searchBookByTitle(search);
    searchBookByAuthor(search);
    searchBookByPYear(p);
}