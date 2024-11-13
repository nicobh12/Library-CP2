#ifndef MESSAGES_H
#define MESSAGES_H
#define MAX_LEN 50

#include <cstdio>
#include <cstdlib>
#include "structs.h"
#include <locale.h>
#include <cstring>
#include "login.h"
#include "view.h"
#include "search.h"
#include "actions.h"
#include "books.h"

// Mensajes generales
const char *fileOpenError = "\nError de validacion o al abrir el archivo\n";

// Mensajes para la validacion de inicio de sesion y acciones en login.cpp
const char *loggedSuccessfully = "\nSInicio de sesion exitoso\n";
const char *nLoggedSuccessfully = "\nHubo un error al iniciar sesion\n";

const char *signInSuccessfully = "\nEl registro fue realizado con exito\n";
const char *nSignInSuccessfully = "\nNo se pudo realizar el registro\n";

// Mensajes para otras acciones
const char *userNotFound = "\nUsuario no encontrado\n";
const char *userBlocked = "\nUsuario bloqueado\n";
const char *userUnblocked = "\nUsuario desbloqueado\n";
const char *feePaid = "\nSe ha pagado la deuda\n";
const char *noFeeToPay = "\nEl usuario no tiene una deuda activa\n";
const char *feeAssigned = "\nDeuda asignada exitosamente\n";
const char *dataChanged = "\nDatos actualizados exitosamente\n";
const char *bookAddedSuccessfully = "\nLibro agregado correctamente\n";
const char *alreadyTwoBooksBorrowed = "\nTransaccion excede el limite de prestamos\n";
const char *bookNotAvailable = "\nLibro no disponible\n";
const char *bookBorrowedSuccessfully = "\nLibro prestado exitosamente";
const char *bookNotFound = "\nLibro no encontrado";
const char *bookDeletedSuccessfully = "\nLibro eliminado exitosamente\n";
const char *bookModifiedSuccessfully = "\nLibro modificado exitosamente\n";
const char *userDeletedSuccessfully = "\nUsuario eliminado exitosamente\n";
const char *adminDeletedSuccessfully = "\nAdministrador eliminado correctamente\n";
const char *adminNotFound = "\nAdministrador no encontrado\n";
const char *usersSortedSuccessfully = "\neUsuarios ordenados correctamente";
const char *adminsSortedSuccessfully = "\nAdministradores ordenados correctamente";
const char *booksSortedSuccessfully = "\nLibros ordenados correctamente";
const char *genreNotFound = "\nGenero no encontrado\n";
const char *noBooksInGenre = "\nNo hay libros del genero buscado\n";

// Para listar elementos
void listar(const char *elements)
{
    printf("\nLista de %s\n", elements);
}
// Operación para abrir archivos
FILE *openFileR(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // Open binary file
    if (file == NULL)
    {
        printf("%s", fileOpenError);
        return NULL; // Return NULL to indicate failure
    }
    return file; // Return the file pointer on success
}

FILE *openFileRPlus(const char *filename)
{
    FILE *file = fopen(filename, "r+b"); // Open binary file
    if (file == NULL)
    {
        printf("%s", fileOpenError);
        return NULL; // Return NULL to indicate failure
    }
    return file; // Return the file pointer on success
}

FILE *openFileA(const char *filename)
{
    FILE *file = fopen(filename, "ab"); // Open binary file
    if (file == NULL)
    {
        printf("%s", fileOpenError);
        return NULL; // Return NULL to indicate failure
    }
    return file; // Return the file pointer on success
}

FILE *openFileW(const char *filename)
{
    FILE *file = fopen(filename, "wb"); // Open binary file
    if (file == NULL)
    {
        printf("%s", fileOpenError);
        return NULL; // Return NULL to indicate failure
    }
    return file; // Return the file pointer on success
}

const char *genreToString(genre g)
{
    switch (g)
    {
    case FICCION:
        return "Ficcion";
    case NO_FICCION:
        return "No Ficcion";
    case MISTERIO:
        return "Misterio";
    case FANTASIA:
        return "Fantasia";
    case CIENCIA_FICCION:
        return "Ciencia Ficcion";
    case BIOGRAFIA:
        return "Biografia";
    case HISTORIA:
        return "Historia";
    case POESIA:
        return "Poesia";
    case YOUNG_ADULT:
        return "Young Adult"; // Lo dejo igual, ya que "Young Adult" es comúnmente usado en español también
    case OTRO:
        return "Otro";
    default:
        return "Desconocido"; // En caso de valores fuera de rango
    }
}

// Menús

void searchUserMenu()
{
    char option;
    char buffer[50]; // Buffer para entradas de texto
    int id;

    do
    {
        // Mostrar el menú de opciones
        printf("\n==== Menu de Busqueda de Usuario ====\n");
        printf("1. Buscar por nombre\n");
        printf("2. Buscar por apellido\n");
        printf("3. Buscar por ID\n");
        printf("0. Volver al menu anterior\n");
        printf("Seleccione una opción: ");

        // Leer la opción del usuario y limpiar el buffer
        option = getchar();
        fflush(stdin);
        system("cls");

        switch (option)
        {
        case '1': // Buscar por nombre
            printf("Ingrese el nombre a buscar: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea
            searchUserByName(buffer);
            break;

        case '2': // Buscar por apellido
            printf("Ingrese el apellido a buscar: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea
            searchUserByLName(buffer);
            break;

        case '3': // Buscar por ID
            printf("Ingrese el ID del usuario: ");
            scanf("%d", &id);
            fflush(stdin);
            searchUserById(id);
            break;

        case '0': // Volver al menú anterior
            printf("Volviendo al menu anterior...\n");
            break;

        default: // Opción inválida
            printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
        getchar();

        system("cls");
    } while (option != '0');
}

void searchBookMenu()
{
    int option = 0;

    printf("\n--- MENU DE BUSQUEDA DE LIBROS ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por titulo\n");
    printf("3. Buscar por autor\n");
    printf("4. Buscar por genero\n");
    printf("5. Buscar sin campo especifico\n");
    printf("0. Salir\n");
    printf("Ingrese una opción: ");
    scanf("%d", &option);
    getchar();

    fflush(stdin);
    system("cls");

    switch (option)
    {
    case 1:
    {
        int id;
        printf("Ingrese el ID del libro: ");
        scanf("%d", &id);
        searchBookById(id);
        break;
    }
    case 2:
    {
        char title[60];
        printf("Ingrese el titulo del libro: ");
        scanf(" %[^\n]", title);
        searchBookByTitle(title);
        break;
    }
    case 3:
    {
        char author[40];
        printf("Ingrese el autor del libro: ");
        scanf(" %[^\n]", author);
        searchBookByAuthor(author);
        break;
    }
    case 4:
    {
        char genre[20];
        printf("Ingrese el genero del libro: ");
        scanf(" %[^\n]", genre);
        searchByGenre(genre);
        break;
    }
    case 5:
        // Llamar a la nueva función para búsqueda sin campo específico
        searchBook();
        break;
    case 0:
        printf("Saliendo del menu de búsqueda de libros...\n");
        break;
    default:
        printf("Opción no valida. Intente de nuevo.\n");
        break;
    }
    getchar();

    system("cls");
}

void guestMenu(int id, bool admin)
{
    int option = 0;
    do
    {
        printf("\n--- MENU INVITADO ---\n");
        printf("1. Iniciar sesion como administrador\n");
        printf("2. Iniciar sesion como usuario\n");
        printf("3. Registrarse\n");
        printf("4. Ver lista de libros disponibles\n");
        printf("5. Buscar libros\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &option);
        getchar();

        fflush(stdin);
        system("cls");

        char clave[MAX_LEN];
        char password[MAX_LEN];

        switch (option)
        {
        case 1:
            printf("Ingrese la clave: ");
            fgets(clave, MAX_LEN, stdin);
            clave[strcspn(clave, "\n")] = '\0';

            printf("Ingrese la contraseña: ");
            fgets(password, MAX_LEN, stdin);

            login(clave, password, true, id, admin);
            break;
        case 2:
            printf("Ingrese la clave: ");
            fgets(clave, MAX_LEN, stdin);
            clave[strcspn(clave, "\n")] = '\0';

            printf("Ingrese la contraseña: ");
            fgets(password, MAX_LEN, stdin);

            login(clave, password, false, id, admin);
            break;
        case 3:
            signIn(false, id);
            break;
        case 4:
            viewAllBooks(false);
            break;
        case 5:
            searchBookMenu();
            break;
        case 0:
            printf("Saliendo del programa...\n");
            exit(0);
            break;
        default:
            printf("Opcion no válida. Intente de nuevo.\n");
        }
        getchar();
        system("cls");

    } while (option != 0);
}

void userMenu(int id, bool admin)
{
    int option = 0;
    do
    {
        printf("\n--- MENU USUARIO ---\n");
        printf("1. Ver mi informacion\n");
        printf("2. Ver lista de libros\n");
        printf("3. Buscar un libro\n");
        printf("4. Devolver un libro\n");
        printf("5. Pagar deuda\n");
        printf("6. Actualizar mis datos\n");
        printf("7. Cerrar sesion\n");
        printf("8. Eliminar mi cuenta\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &option);
        getchar();

        fflush(stdin);
        system("cls");

        switch (option)
        {
        case 1:
            viewUserInfo(id);
            break;
        case 2:
            viewAllBooks(false);
            printf("\n¿Desea prestar un libro? (1: Sí, 0: No): ");
            int borrowOption;
            scanf("%d", &borrowOption);
            if (borrowOption == 1)
            {
                int bookId;
                printf("Ingrese el ID del libro a prestar: ");
                scanf("%d", &bookId);
                borrowBook(id, bookId);
            }
            break;
        case 3:
            searchBookMenu();
            break;
        case 4:
            int bookId;
            returnBook(id, bookId); // Función para devolver un libro
            break;
        case 5:
            payUp(id);
            break;
        case 6:
            changeData(id);
            break;
        case 7:
            id = 0;
            printf("Sesión cerrada.\n");
            option = 0;
            guestMenu(id, false);
            break;
        case 8:
            deleteUser(id);
            id = 0;
            break;
        case 0:
            printf("Saliendo del programa...\n");
            exit(0);
            break;
        default:
            printf("Opcion no válida. Intente de nuevo.\n");
        }
        getchar();
        system("cls");

    } while (option != 0);
}

void adminMenu(int id)
{
    int option = 0;
    do
    {
        printf("\n--- MENU ADMINISTRADOR ---\n");
        printf("1. Ver lista de libros\n");
        printf("2. Agregar libros\n");
        printf("3. Modificar libro\n");
        printf("4. Ver usuarios\n");
        printf("5. Buscar usuarios\n");
        printf("6. Cambiar estado de usuario (bloquear/desbloquear)\n");
        printf("7. Actualizar datos de usuario\n");
        printf("8. Asignar deuda a usuario\n");
        printf("9. Eliminar usuario\n");
        printf("10. Registrar nuevo administrador\n");
        printf("11. Ver lista de administradores\n");
        printf("12. Eliminar administrador\n");
        printf("13. Cerrar sesion\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &option);
        getchar();

        fflush(stdin);
        system("cls");

        switch (option)
        {
        case 1:
            viewAllBooks(true);
            break;
        case 2:
            int numBooks;
            printf("Ingrese la cantidad de libros a agregar: ");
            scanf("%d", &numBooks);
            addBook(numBooks);
            break;
        case 3:
            int bookId;
            printf("Ingrese el ID del libro a modificar: ");
            scanf("%d", &bookId);
            modifyBook(bookId);
            break;
        case 4:
            viewAllUsers();
            break;
        case 5:
            searchUserMenu();
            break;
        case 6:
            printf("Ingrese el ID del usuario para cambiar su estado: ");
            int userId;
            scanf("%d", &userId);
            blockUnblockUser(userId);
            break;
        case 7:
            printf("Ingrese el ID del usuario a actualizar: ");
            scanf("%d", &userId);
            changeData(userId);
            break;
        case 8:
            printf("Ingrese el ID del usuario para asignar deuda: ");
            scanf("%d", &userId);
            assignFee(userId);
            break;
        case 9:
            printf("Ingrese el ID del usuario a eliminar: ");
            scanf("%d", &userId);
            deleteUser(userId);
            break;
        case 10:
            signIn(true, id);
            break;
        case 11:
            viewAdmins();
            break;
        case 12:
            deleteAdmin(id);
            id = 0;
            break;
        case 13:
            id = 0;
            printf("Sesion cerrada.\n");
            option = 0;
            guestMenu(id, false);
            break;
        case 0:
            printf("Saliendo del programa...\n");
            exit(0);
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
        getchar();
        system("cls");

    } while (option != 0);
}

void mainMenu(int &id, bool &admin)
{
    if (id == 0)
        guestMenu(id, admin);
    else if (!admin)
        userMenu(id, admin);
    else
        adminMenu(id);
}

#endif