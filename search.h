#ifndef SEARCH_FUNCTIONS_H
#define SEARCH_FUNCTIONS_H

#include "structs.h"  // Asegúrate de incluir la definición de user, book, etc.
#include "messages.h" // Si estás utilizando constantes o mensajes definidos aquí

// Funciones de búsqueda de usuarios
void saveAndDisplayUser(FILE *file, const user &foundUser);
void searchUserById(int id);
void searchUserByName(const char *name);
void searchUserByLName(const char *lname);
void searchUser(); // Función que llama a las otras funciones de búsqueda de usuarios

// Funciones de búsqueda de libros
void saveAndDisplayBook(FILE *file, const book &foundBook);
void searchBookById(int id);
void searchBookByTitle(const char *title);
void searchBookByAuthor(const char *author);
void searchByGenre(const char *g);
void searchBookByPYear(int year);
void searchBook(); // Función que llama a las otras funciones de búsqueda de libros

#endif // SEARCH_FUNCTIONS_H
