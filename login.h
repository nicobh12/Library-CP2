/*Funciones para el uso de inicio de sesion y registro de administradores y usuarios*/

#ifndef LOGIN_H
#define LOGIN_H

void login(char *key, char *pass, bool isAdmin, int &id, bool &admin);
int signIn(bool isAdmin, int &id);

#endif