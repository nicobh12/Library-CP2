#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

typedef enum {
    FICTION,
    NON_FICTION,
    MYSTERY,
    FANTASY,
    SCIENCE_FICTION,
    BIOGRAPHY,
    HISTORY,
    POETRY,
    YOUNG_ADULT,
    OTHER
} genre;

typedef struct {
    char title[60];
    char author[40];
    genre g;
    int pYear;
} book;

typedef struct {
    char name[20];
    char lname[40];
    int adminId;
} admin;

typedef struct {
    book b;
    //Añadir fecha de devolucion
} borrowB;

typedef struct {
    char name[20];
    char lname[40];
    int id;
    book borrowed1;
    book borrowed2;
    bool blocked;
    int owed;
} user;

typedef struct {
    book b;
    int total;
    user *borrows;
    int available;
    int id;
} infoBooks;

typedef struct{
    char subject[40];
    char body[500];
} observaciones;

#endif