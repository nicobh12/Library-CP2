#ifndef LOGIN_H
#define LOGIN_H

void login(char *key, char *pass, bool isAdmin, int &id, bool &admin);
int signIn(bool isAdmin, int &id);

#endif