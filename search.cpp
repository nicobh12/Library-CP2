#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "structs.h"
#include "messages.h"

void displayUser(const user& foundUser) {
    printf("ID: %d\nNombre: %s %s\nCorreo: %s\nBloqueado: %s\nDeuda: %d\n\n",
           foundUser.id, foundUser.name, foundUser.lname, foundUser.mail,
           foundUser.blocked ? "Sí" : "No", foundUser.owed);
}

void searchUserById(int id) {
    FILE* file = openFileR("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;
    printf("\n--- Busqueda por ID ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == id) {
            displayUser(currentUser);
            found = true;
            break;
        }
    }
    if (!found) printf("No se encontro un usuario con ID: %d\n", id);

    fclose(file);
}

void searchUserByName(const char* name) {
    FILE* file = openFileR("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;
    printf("\n--- Busqueda por Nombre ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (strcmp(currentUser.name, name) == 0) {
            displayUser(currentUser);
            found = true;
        }
    }
    if (!found) printf("No se encontro un usuario con el nombre: %s\n", name);

    fclose(file);
}

void searchUserByLName(const char* lname) {
    FILE* file = openFileR("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;
    printf("\n--- Busqueda por Apellido ---\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (strcmp(currentUser.lname, lname) == 0) {
            displayUser(currentUser);
            found = true;
        }
    }
    if (!found) printf("No se encontro un usuario con el apellido: %s\n", lname);

    fclose(file);
}

void searchUser() {
    char search[40];
    printf("Ingrese texto a buscar: ");
    scanf("%[^\n]%*c", search);

    // Verificar si 'search' es un numero
    int id = atoi(search);
    if (id != 0) {  // Es un numero, por lo tanto, buscar por ID
        searchUserById(id);
    } else {  // No es un numero, buscar por nombre o apellido
        searchUserByName(search);
        searchUserByLName(search);
    }
}

void displayBook(const book& foundBook) {
    printf("Titulo: %s\nAutor: %s\nGenero: %d\nPublicacion: %d\n\n",
           foundBook.title, foundBook.author, genreToString(foundBook.g), foundBook.pYear);
}

void searchBookById(int id) {
    FILE* file = openFileR("books.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Busqueda por ID ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.id == id) {
            displayBook(currentBook.b);
            found = true;
            break;
        }
    }
    if (!found) printf("No se encontro un libro con ID: %d\n", id);

    fclose(file);
}

void searchBookByTitle(const char* title) {
    FILE* file = openFileR("books.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Busqueda por Titulo ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (strcmp(currentBook.b.title, title) == 0) {
            displayBook(currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontro un libro con el titulo: %s\n", title);

    fclose(file);
}

void searchBookByAuthor(const char* author) {
    FILE* file = openFileR("books.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Busqueda por Autor ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (strcmp(currentBook.b.author, author) == 0) {
            displayBook(currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontro un libro del autor: %s\n", author);

    fclose(file);
}

void searchByGenre(int genreNumber) {
    genre searchGenre;

    switch (genreNumber) {
        case 1: searchGenre = FICCION; break;
        case 2: searchGenre = NO_FICCION; break;
        case 3: searchGenre = MISTERIO; break;
        case 4: searchGenre = FANTASIA; break;
        case 5: searchGenre = CIENCIA_FICCION; break;
        case 6: searchGenre = BIOGRAFIA; break;
        case 7: searchGenre = HISTORIA; break;
        case 8: searchGenre = POESIA; break;
        case 9: searchGenre = YOUNG_ADULT; break;
        case 10: searchGenre = OTRO; break;
        default:
            printf("Genero no valido.\n");
            return;
    }

    FILE *file = openFileR("books.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;

    printf("Libros encontrados en el genero seleccionado:\n");
    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.b.g == searchGenre) {
            printf("Titulo: %s\nAutor: %s\nPublicacion: %d\n\n",
                   currentBook.b.title, currentBook.b.author, currentBook.b.pYear);
            found = true;
        }
    }

    if (!found) printf("%s\n", noBooksInGenre);
    fclose(file);
}

void searchBookByPYear(int year) {
    FILE* file = openFileR("books.dat");
    if (!file) return;

    infoBooks currentBook;
    bool found = false;
    printf("\n--- Busqueda por Publicacion ---\n");

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1) {
        if (currentBook.b.pYear == year) {
            displayBook(currentBook.b);
            found = true;
        }
    }
    if (!found) printf("No se encontro un libro publicado en %d\n", year);

    fclose(file);
}

void searchBook(){
    char search[50];

    printf("\nIngrese texto a buscar\n");
    scanf("%[^\n]%*c", &search);

    int p = atoi(search);

    searchBookById(p);
    searchBookByTitle(search);
    searchBookByAuthor(search);
    searchBookByPYear(p);
}