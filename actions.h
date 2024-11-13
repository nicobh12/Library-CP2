#ifndef ADMIN_USER_FUNCTIONS_H
#define ADMIN_USER_FUNCTIONS_H

#include "structs.h"
#include "messages.h"
#include <cstdio>

// Funciones para manipular usuarios
void blockUnblockUser(int userId);
void payUp(int userId);
void assignFee(int userId);
void changeData(int id);
void deleteUser(int id);

// Funciones para manipular administradores
void deleteAdmin(int id);

// Funciones para ordenar usuarios, administradores y libros
void sortUsers();
void sortAdmins();
void sortBooks();

#endif // ADMIN_USER_FUNCTIONS_H
