#include "structs.h"
#include "messages.h"
#include <cstdio>
#include <ctime>
#include <cstring>

void assignDueDate(Date &dueDate)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    dueDate.day = tm_info->tm_mday;
    dueDate.month = tm_info->tm_mon + 1;
    dueDate.year = tm_info->tm_year + 1900;

    dueDate.day += 14; // Asignamos dos semanas adicionales
    if (dueDate.day > 30)
    { // Simplificación para manejar cambios de mes
        dueDate.day -= 30;
        dueDate.month++;
        if (dueDate.month > 12)
        {
            dueDate.month = 1;
            dueDate.year++;
        }
    }
}

void addBook(int n)
{
    FILE *file = openFileA("libros.dat");
    if (!file)
        return;

    infoBooks newBook;
    for (int i = 0; i < n; i++)
    {
        printf("\nIngrese el título del libro: ");
        scanf("%s", newBook.b.title);

        printf("Ingrese el autor del libro: ");
        scanf("%s", newBook.b.author);

        printf("Ingrese el género (0-9): ");
        scanf("%d", reinterpret_cast<int *>(&newBook.b.g));

        printf("Ingrese el año de publicación: ");
        scanf("%d", &newBook.b.pYear);

        printf("Ingrese la cantidad total de este libro: ");
        scanf("%d", &newBook.total);
        newBook.available = newBook.total;

        // Asignar ID único
        newBook.id = i + 1; // Simplemente usa un índice como ID único (mejorar si se requiere un ID específico)

        fwrite(&newBook, sizeof(infoBooks), 1, file);
        printf("%s", bookAddedSuccessfully);
    }
    fclose(file);
}

void borrowBook(int userId, int bookId)
{
    FILE *userFile = openFileRPlus("usuarios.dat");
    FILE *bookFile = openFileRPlus("libros.dat");

    if (!userFile || !bookFile)
        return;

    user currentUser;
    bool userFound = false;

    while (fread(&currentUser, sizeof(user), 1, userFile) == 1)
    {
        if (currentUser.id == userId)
        {
            userFound = true;

            if (currentUser.blocked)
            {
                printf("%s", userBlocked);
                break;
            }
            if (currentUser.borrowed1.b.title[0] != '\0' && currentUser.borrowed2.b.title[0] != '\0')
            {
                printf("%s", alreadyTwoBooksBorrowed);
                break;
            }

            infoBooks currentBook;
            bool bookFound = false;

            while (fread(&currentBook, sizeof(infoBooks), 1, bookFile) == 1)
            {
                if (currentBook.id == bookId)
                {
                    bookFound = true;

                    if (currentBook.available <= 0)
                    {
                        printf("%s", bookNotAvailable);
                        break;
                    }

                    currentBook.available--;
                    fseek(bookFile, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
                    fwrite(&currentBook, sizeof(infoBooks), 1, bookFile);

                    borrowB newBorrow;
                    newBorrow.b = currentBook.b;
                    assignDueDate(newBorrow.dueDate);

                    if (currentUser.borrowed1.b.title[0] == '\0')
                    {
                        currentUser.borrowed1 = newBorrow;
                    }
                    else
                    {
                        currentUser.borrowed2 = newBorrow;
                    }

                    fseek(userFile, -static_cast<long>(sizeof(user)), SEEK_CUR);
                    fwrite(&currentUser, sizeof(user), 1, userFile);

                    printf("%s", bookBorrowedSuccessfully);
                    break;
                }
            }

            if (!bookFound)
                printf("%s", bookNotFound);
            break;
        }
    }

    if (!userFound)
        printf("%s", userNotFound);

    fclose(userFile);
    fclose(bookFile);
}

void deleteBook(int bookId)
{
    FILE *file = openFileRPlus("libros.dat");
    FILE *tempFile = openFileW("temp.dat");

    if (!file || !tempFile)
        return;

    infoBooks currentBook;
    bool found = false;

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1)
    {
        if (currentBook.id == bookId)
        {
            found = true;
            printf("%s", bookDeletedSuccessfully);
        }
        else
        {
            fwrite(&currentBook, sizeof(infoBooks), 1, tempFile);
        }
    }

    if (!found)
        printf("%s", bookNotFound);

    fclose(file);
    fclose(tempFile);

    remove("libros.dat");
    rename("temp.dat", "libros.dat");
}

void modifyBook(int bookId)
{
    FILE *file = openFileRPlus("libros.dat");
    if (!file)
        return;

    infoBooks currentBook;
    bool found = false;

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1)
    {
        if (currentBook.id == bookId)
        {
            found = true;

            printf("\nIngrese el nuevo título del libro: ");
            scanf("%s", currentBook.b.title);

            printf("Ingrese el nuevo autor del libro: ");
            scanf("%s", currentBook.b.author);

            printf("Ingrese el nuevo género (0-9): ");
            scanf("%d", reinterpret_cast<int *>(&currentBook.b.g));

            printf("Ingrese el nuevo año de publicación: ");
            scanf("%d", &currentBook.b.pYear);

            printf("Ingrese la cantidad total de este libro: ");
            scanf("%d", &currentBook.total);
            currentBook.available = currentBook.total;

            fseek(file, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
            fwrite(&currentBook, sizeof(infoBooks), 1, file);

            printf("%s", bookModifiedSuccessfully);
            break;
        }
    }

    if (!found)
        printf("%s", bookNotFound);

    fclose(file);
}

void returnBook(int userId, int bookId)
{
    FILE *userFile = openFileRPlus("usuarios.dat");
    FILE *bookFile = openFileRPlus("books.dat");

    user currentUser;
    bool foundUser = false;

    // Buscar al usuario en el archivo de usuarios
    while (fread(&currentUser, sizeof(user), 1, userFile) == 1)
    {
        if (currentUser.id == userId)
        {
            foundUser = true;
            break;
        }
    }

    if (!foundUser)
    {
        printf("Usuario no encontrado.\n");
        fclose(userFile);
        fclose(bookFile);
        return;
    }

    // Variable para verificar si se ha devuelto un libro
    bool bookReturned = false;

    // Verificar si el libro a devolver está en `borrowed1`
    if (currentUser.borrowed1.b.title[0] != '\0' && currentUser.borrowed1.b.pYear == bookId)
    {
        // Actualizar la disponibilidad del libro en `libros.dat`
        infoBooks currentBook;
        while (fread(&currentBook, sizeof(infoBooks), 1, bookFile) == 1)
        {
            if (currentBook.id == bookId)
            {
                currentBook.available++;
                fseek(bookFile, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR); // Volver atrás para reescribir
                fwrite(&currentBook, sizeof(infoBooks), 1, bookFile);
                break;
            }
        }

        // Eliminar la información de `borrowed1`
        memset(&currentUser.borrowed1, 0, sizeof(borrowB));
        bookReturned = true;
    }
    // Si el libro no estaba en `borrowed1`, verificar en `borrowed2`
    else if (currentUser.borrowed2.b.title[0] != '\0' && currentUser.borrowed2.b.pYear == bookId)
    {
        // Actualizar la disponibilidad del libro en `libros.dat`
        infoBooks currentBook;
        fseek(bookFile, 0, SEEK_SET); // Volver al inicio del archivo de libros
        while (fread(&currentBook, sizeof(infoBooks), 1, bookFile) == 1)
        {
            if (currentBook.id == bookId)
            {
                currentBook.available++;
                fseek(bookFile, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
                fwrite(&currentBook, sizeof(infoBooks), 1, bookFile);
                break;
            }
        }

        // Eliminar la información de `borrowed2`
        memset(&currentUser.borrowed2, 0, sizeof(borrowB));
        bookReturned = true;
    }

    if (bookReturned)
    {
        // Reescribir los datos del usuario en `usuarios.dat`
        fseek(bookFile, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
        fwrite(&currentUser, sizeof(user), 1, userFile);
        printf("Libro devuelto correctamente.\n");
    }
    else
    {
        printf("El usuario no tiene prestado el libro con ID %d.\n", bookId);
    }

    fclose(userFile);
    fclose(bookFile);
}