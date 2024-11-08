// messages.h

#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdio>

// Declare the variables as extern
extern const char* fileOpenError;
extern const char* loggedSuccessfully;
extern const char* nLoggedSuccessfully;
extern const char* signInSuccessfully;
extern const char* nSignInSuccessfully;

// Declare the functions (no definitions here, just declarations)
void listar(const char* str);

FILE* openFileR(const char* filename);
FILE* openFileA(const char* filename);

#endif  // MESSAGES_H
