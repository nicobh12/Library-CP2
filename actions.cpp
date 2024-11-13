#include "structs.h"
#include "messages.h"
#include <cstdio>
#include <cstring>
#include <algorithm>

void blockUnblockUser(int userId)
{
    FILE *file = openFileRPlus("usuarios.dat");
    if (!file)
        return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id == userId)
        {
            found = true;
            currentUser.blocked = !currentUser.blocked;                            // Cambia el estado
            fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);               // Volver al inicio del usuario actual
            fwrite(&currentUser, sizeof(user), 1, file);                           // Actualizar en el archivo
            printf(currentUser.blocked ? "%s" : "%s", userBlocked, userUnblocked); // Mensaje de confirmación
            break;
        }
    }

    if (!found)
        printf("%s", userNotFound); // Mensaje de error si no se encuentra el usuario
    fclose(file);
}

void payUp(int userId)
{
    FILE *file = openFileRPlus("usuarios.dat");
    if (!file)
        return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id == userId)
        {
            found = true;
            if (currentUser.owed > 0)
            {
                currentUser.owed = 0; // Eliminar deuda
                fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);
                fwrite(&currentUser, sizeof(user), 1, file);
                printf("%s", feePaid);
            }
            else
            {
                printf("%s", noFeeToPay);
            }
            break;
        }
    }

    if (!found)
        printf("%s", userNotFound);
    fclose(file);
}

void assignFee(int userId)
{
    FILE *file = openFileRPlus("usuarios.dat");
    if (!file)
        return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id == userId)
        {
            found = true;
            currentUser.owed += 10; // Asignar multa fija (puedes cambiar el valor si es necesario)
            fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);
            fwrite(&currentUser, sizeof(user), 1, file);
            printf("%s", feeAssigned);
            break;
        }
    }

    if (!found)
        printf("%s", userNotFound);
    fclose(file);
}

void changeData(int id)
{
    FILE *file = openFileRPlus("usuarios.dat");
    if (!file)
        return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id == id)
        {
            found = true;
            printf("\nIngrese el nuevo nombre del usuario: ");
            scanf("%s", currentUser.name);

            printf("\nIngrese el nuevo apellido del usuario: ");
            scanf("%s", currentUser.lname);

            printf("\nIngrese el nuevo correo del usuario: ");
            scanf("%s", currentUser.mail);

            fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);
            fwrite(&currentUser, sizeof(user), 1, file);
            printf("%s", dataChanged); // Mensaje de confirmación
            break;
        }
    }

    if (!found)
        printf("%s", userNotFound);
    fclose(file);
}

void deleteUser(int id)
{
    FILE *file = openFileR("usuarios.dat");
    FILE *tempFile = openFileW("temp.dat");

    if (!file || !tempFile)
        return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id == id)
        {
            found = true;
            printf("%s", userDeletedSuccessfully);
        }
        else
        {
            fwrite(&currentUser, sizeof(user), 1, tempFile);
        }
    }

    if (!found)
        printf("%s", userNotFound);

    fclose(file);
    fclose(tempFile);

    remove("usuarios.dat");
    rename("temp.dat", "usuarios.dat");
}

void deleteAdmin(int id)
{
    FILE *file = openFileR("admins.dat");
    FILE *tempFile = openFileW("temp.dat");

    if (!file || !tempFile)
        return;

    admin currentAdmin;
    bool found = false;

    while (fread(&currentAdmin, sizeof(admin), 1, file) == 1)
    {
        if (currentAdmin.adminId == id)
        {
            found = true;
            printf("%s", adminDeletedSuccessfully);
        }
        else
        {
            fwrite(&currentAdmin, sizeof(admin), 1, tempFile);
        }
    }

    if (!found)
        printf("%s", adminNotFound);

    fclose(file);
    fclose(tempFile);

    remove("admins.dat");
    rename("temp.dat", "admins.dat");
}

void sortUsers()
{
    FILE *file = openFileR("usuarios.dat");
    if (!file)
        return;

    user users[100];
    int count = 0;

    while (fread(&users[count], sizeof(user), 1, file) == 1)
    {
        count++;
    }
    fclose(file);

    std::sort(users, users + count, [](const user &a, const user &b)
              { return strcasecmp(a.lname, b.lname) < 0; });

    file = openFileW("usuarios.dat");
    fwrite(users, sizeof(user), count, file);
    fclose(file);
    printf("%s", usersSortedSuccessfully);
}

void sortAdmins()
{
    FILE *file = openFileR("admins.dat");
    if (!file)
        return;

    admin admins[100];
    int count = 0;

    while (fread(&admins[count], sizeof(admin), 1, file) == 1)
    {
        count++;
    }
    fclose(file);

    std::sort(admins, admins + count, [](const admin &a, const admin &b)
              { return strcasecmp(a.lname, b.lname) < 0; });

    file = openFileW("admins.dat");
    fwrite(admins, sizeof(admin), count, file);
    fclose(file);
    printf("%s", adminsSortedSuccessfully);
}

void sortBooks()
{
    FILE *file = openFileR("libros.dat");
    if (!file)
        return;

    infoBooks books[100];
    int count = 0;

    while (fread(&books[count], sizeof(infoBooks), 1, file) == 1)
    {
        count++;
    }
    fclose(file);

    std::sort(books, books + count, [](const infoBooks &a, const infoBooks &b)
              { return strcasecmp(a.b.title, b.b.title) < 0; });

    file = openFileW("libros.dat");
    fwrite(books, sizeof(infoBooks), count, file);
    fclose(file);
    printf("%s", booksSortedSuccessfully);
}
