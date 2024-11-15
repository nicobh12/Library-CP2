/*Structs usadas en el archivo en general*/

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

typedef enum
{
    FICCION,
    NO_FICCION,
    MISTERIO,
    FANTASIA,
    CIENCIA_FICCION,
    BIOGRAFIA,
    HISTORIA,
    POESIA,
    YOUNG_ADULT,
    OTRO
} genre;

typedef struct
{
    char title[60];
    char author[40];
    genre g;
    int pYear;
} book;

typedef struct
{
    char name[20];
    char lname[40];
    int adminId;
    char pass[50];
} admin;

typedef struct
{
    int day;
    int month;
    int year;
} Date;

typedef struct
{
    book b;
    Date dueDate;
} borrowB;

typedef struct
{
    char name[20];
    char lname[40];
    int id;
    char mail[50];
    borrowB borrowed1;
    borrowB borrowed2;
    int idb1;
    int idb2;
    bool blocked;
    int owed;
    char pass[50];
} user;

typedef struct
{
    book b;
    int total;
    user *borrows;
    int available;
    int id;
} infoBooks;

#endif