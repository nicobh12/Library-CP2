#include "structs.h"
#include "messages.h"
#include <cstdio>
#include <cstring>

void blockUnblockUser(int userId) {
    FILE* file = openFileRPlus("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == userId) {
            found = true;
            currentUser.blocked = !currentUser.blocked; // Cambia el estado
            fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR); // Volver al inicio del usuario actual
            fwrite(&currentUser, sizeof(user), 1, file); // Actualizar en el archivo
            printf(currentUser.blocked ? "%s" : "%s", userBlocked, userUnblocked); // Mensaje de confirmación
            break;
        }
    }

    if (!found) printf("%s", userNotFound); // Mensaje de error si no se encuentra el usuario
    fclose(file);
}

void payUp(int userId) {
    FILE* file = openFileRPlus("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == userId) {
            found = true;
            if (currentUser.owed > 0) {
                currentUser.owed = 0; // Eliminar deuda
                fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);
                fwrite(&currentUser, sizeof(user), 1, file);
                printf("%s", feePaid);
            } else {
                printf("%s", noFeeToPay);
            }
            break;
        }
    }

    if (!found) printf("%s", userNotFound);
    fclose(file);
}

void assignFee(int userId) {
    FILE* file = openFileRPlus("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == userId) {
            found = true;
            currentUser.owed += 10; // Asignar multa fija (puedes cambiar el valor si es necesario)
            fseek(file, -static_cast<long>(sizeof(user)), SEEK_CUR);
            fwrite(&currentUser, sizeof(user), 1, file);
            printf("%s", feeAssigned);
            break;
        }
    }

    if (!found) printf("%s", userNotFound);
    fclose(file);
}

void changeData(int id) {
    FILE* file = openFileRPlus("usuarios.dat");
    if (!file) return;

    user currentUser;
    bool found = false;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id == id) {
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

    if (!found) printf("%s", userNotFound);
    fclose(file);
}

void deleteUser(int id);

void deleteAdmin(int id);

void sortFileAU(const char* filename);

void sortBooks(const char* filename);
