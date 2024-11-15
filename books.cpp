#include "structs.h"
#include "messages.h"
#include "actions.h"
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
    { // Simplificacion para manejar cambios de mes
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
    FILE *file = openFileA("books.dat");
    if (!file)
        return;

    infoBooks newBook;
    for (int i = 0; i < n; i++)
    {
        printf("\nIngrese el titulo del libro: ");
        scanf(" %[^\n]", newBook.b.title);

        printf("Ingrese el autor del libro: ");
        scanf(" %[^\n]", newBook.b.author);

        printf("Ingrese el genero (0-9): \n");
        printGenresList();
        scanf("%d", reinterpret_cast<int *>(&newBook.b.g));

        printf("Ingrese fecha de publicacion (aaaa): ");
        scanf("%d", &newBook.b.pYear);

        printf("Ingrese la cantidad total de este libro: ");
        scanf("%d", &newBook.total);
        newBook.available = newBook.total;

        // Asignar ID unico
        newBook.id = i + 1; // Simplemente usa un indice como ID unico (mejorar si se requiere un ID especifico)

        fwrite(&newBook, sizeof(infoBooks), 1, file);
        printf("%s", bookAddedSuccessfully);
    }
    fclose(file);

    sortBooks();
}

void returnBook(int userId, int bookId)
{
    FILE *userFile = openFileRPlus("usuarios.dat");
    FILE *bookFile = openFileRPlus("books.dat");

    if (!userFile || !bookFile)
        return;

    user currentUser;
    bool userFound = false;

    while (fread(&currentUser, sizeof(user), 1, userFile) == 1)
    {
        if (currentUser.id == userId)
        {
            userFound = true;

            // Verificar si el usuario tiene prestado el libro con el ID especificado
            bool bookFound = false;
            if (currentUser.borrowed1.b.title[0] != '\0' && currentUser.idb1 == bookId)
            {
                bookFound = true;
                currentUser.borrowed1.b.title[0] = '\0'; // Vaciar la informacion del libro
            }
            else if (currentUser.borrowed2.b.title[0] != '\0' && currentUser.idb2 == bookId)
            {
                bookFound = true;
                currentUser.borrowed2.b.title[0] = '\0'; // Vaciar la informacion del libro
            }

            if (!bookFound)
            {
                printf("%s", bookNotBorrowed);
                break;
            }

            // Buscar y actualizar el libro en books.dat
            infoBooks currentBook;
            bool bookUpdated = false;
            while (fread(&currentBook, sizeof(infoBooks), 1, bookFile) == 1)
            {
                if (currentBook.id == bookId)
                {
                    currentBook.available++;
                    fseek(bookFile, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
                    fwrite(&currentBook, sizeof(infoBooks), 1, bookFile);
                    bookUpdated = true;
                    break;
                }
            }

            if (!bookUpdated)
            {
                printf("%s", bookNotFound);
                break;
            }

            // Actualizar la informacion del usuario en usuarios.dat
            fseek(userFile, -static_cast<long>(sizeof(user)), SEEK_CUR);
            fwrite(&currentUser, sizeof(user), 1, userFile);

            printf("%s", bookReturnedSuccessfully); // Mensaje de confirmacion
            break;
        }
    }

    if (!userFound)
        printf("%s", userNotFound);

    fclose(userFile);
    fclose(bookFile);
}


void borrowBook(int userId, int bookId)
{
    FILE *userFile = openFileRPlus("usuarios.dat");
    FILE *bookFile = openFileRPlus("books.dat");

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
                        currentUser.idb1 = currentBook.id;
                    }
                    else
                    {
                        currentUser.borrowed2 = newBorrow;
                        currentUser.idb2 = currentBook.id;
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
    FILE *file = openFileRPlus("books.dat");
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

    remove("books.dat");
    rename("temp.dat", "books.dat");
}

void modifyBook(int bookId)
{
    FILE *file = openFileRPlus("books.dat");
    if (!file)
        return;

    infoBooks currentBook;
    bool found = false;

    while (fread(&currentBook, sizeof(infoBooks), 1, file) == 1)
    {
        if (currentBook.id == bookId)
        {
            found = true;
            int choice;

            do
            {
                printf("\nSeleccione el campo que desea modificar:\n");
                printf("1. Titulo\n");
                printf("2. Autor\n");
                printf("3. Genero\n");
                printf("4. Fecha de Publicacion\n");
                printf("5. Cantidad Total\n");
                printf("0. Guardar y salir\n");
                printf("Opcion: ");
                scanf("%d", &choice);

                switch (choice)
                {
                    case 1:
                        printf("\nIngrese el nuevo titulo del libro: ");
                        scanf(" %[^\n]", currentBook.b.title);
                        break;
                    case 2:
                        printf("Ingrese el nuevo autor del libro: ");
                        scanf(" %[^\n]", currentBook.b.author);
                        break;
                    case 3:
                        printf("Ingrese el nuevo genero (0-9): ");
                        scanf("%d", (int *)&currentBook.b.g);
                        break;
                    case 4:
                        printf("Ingrese la nueva fecha de publicacion: ");
                        scanf("%d", &currentBook.b.pYear);
                        break;
                    case 5:
                        printf("Ingrese la cantidad total de este libro: ");
                        scanf("%d", &currentBook.total);
                        currentBook.available = currentBook.total; // Actualiza el disponible al total
                        break;
                    case 0:
                        // Guardar y salir
                        fseek(file, -static_cast<long>(sizeof(infoBooks)), SEEK_CUR);
                        fwrite(&currentBook, sizeof(infoBooks), 1, file);
                        printf("%s", bookModifiedSuccessfully);
                        break;
                    default:
                        printf("Opcion no valida, intente de nuevo.\n");
                }
            } while (choice != 0);

            break;
        }
    }

    if (!found)
        printf("%s", bookNotFound);

    fclose(file);
}
