/*Operaciones relacionadas al manejo de libros por parte de administradores y usuarios*/

#ifndef BOOKS_H
#define BOOKS_H

#include "structs.h"

// Asigna la fecha de vencimiento de un libro (14 dias desde la fecha actual)
void assignDueDate(Date &dueDate);

// Agrega 'n' libros al archivo de libros
void addBook(int n);

//Devuelve libros prestados
void returnBook(int userID, int bookId);

// Permite a un usuario tomar prestado un libro
void borrowBook(int userId, int bookId);

// Elimina un libro del sistema
void deleteBook(int bookId);

// Modifica los datos de un libro existente
void modifyBook(int bookId);

void returnBook(int userId, int bookId);

#endif
