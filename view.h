/*Funciones de visualizacion*/

#ifndef VIEW_FUNCTIONS_H
#define VIEW_FUNCTIONS_H

#include "structs.h"
#include "messages.h"
#include <cstdio>

// Funciones para mostrar usuarios
void viewBlockedUsers();
void viewUnblockedUsers();
void viewAllUsers();

// Funciones para mostrar libros
void viewBorrows(bool isAdmin);
void availableBooks(bool isAdmin);
void viewAllBooks(bool isAdmin);

// Funciones para mostrar informacion de usuarios y administradores
void viewUserInfo(int id);
void viewAdminInfo(int adminId);
void viewAdmins();

#endif // VIEW_FUNCTIONS_H
