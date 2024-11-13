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
extern const char* userNotFound;
extern const char* feePaid;
extern const char* noFeeToPay;
extern const char* feeAssigned;
extern const char* dataChanged;
extern const char* userBlocked;
extern const char* userUnblocked;
extern const char* bookAddedSuccessfully;
extern const char* alreadyTwoBooksBorrowed;
extern const char* bookNotAvailable;
extern const char* bookBorrowedSuccessfully;
extern const char* bookNotFound;
extern const char* bookDeletedSuccessfully;
extern const char* bookModifiedSuccessfully;

void listar(const char* str);

FILE* openFileR(const char* filename);
FILE* openFileRPlus(const char* filename);
FILE* openFileA(const char* filename);
FILE* openFileW(const char* filename);


const char* genreToString(genre g);

#endif  // MESSAGES_H
