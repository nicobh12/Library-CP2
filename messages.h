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

void listar(const char* str);

FILE* openFileR(const char* filename);
FILE* openFileA(const char* filename);

const char* genreToString(genre g);

#endif  // MESSAGES_H
