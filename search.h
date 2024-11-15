#ifndef SEARCH_FUNCTIONS_H
#define SEARCH_FUNCTIONS_H

#include "structs.h"  
#include "messages.h" 

// Funciones de búsqueda de usuarios
void searchUserById(int id);
void searchUserByName(const char *name);
void searchUserByLName(const char *lname);
void searchUser(); // Funcion que llama a las otras funciones de búsqueda de usuarios

// Funciones de búsqueda de libros
void searchBookById(int id);
void searchBookByTitle(const char *title);
void searchBookByAuthor(const char *author);
void searchByGenre(int genreNumber);
void searchBookByPYear(int year);
void searchBook(); // Funcion que llama a las otras funciones de búsqueda de libros

#endif 
