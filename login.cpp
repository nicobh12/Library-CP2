#include "structs.h"
#include "messages.h"
#include "encrypt.h"
#include "actions.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

int loginUser(char *mail, char *pass)
{
    FILE *file = openFileR("usuarios.dat");
    int id = 0;
    user currentUser;

    char decryptedPass[50];

    int desplazamiento = pass[0] % 26; 

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        decrypt_password(currentUser.pass, decryptedPass, desplazamiento);

        if (strcmp(mail, currentUser.mail) == 0 && strcmp(decryptedPass, pass) == 0)
        {
            id = currentUser.id;
            break;
        }
    }

    fclose(file);
    return id;
}

int loginAdmin(char *key, char *pass)
{
    FILE *file = openFileR("admins.dat");
    int id = 0;
    admin currentAdmin;

    int adminId = atoi(key);
    int desplazamiento = pass[0] % 26; // Consistencia en el calculo del desplazamiento

    char decryptedPass[50];

    while (fread(&currentAdmin, sizeof(admin), 1, file) == 1)
    {
        decrypt_password(currentAdmin.pass, decryptedPass, desplazamiento);

        if (adminId == currentAdmin.adminId && strcmp(decryptedPass, pass) == 0)
        {
            id = currentAdmin.adminId;
            break;
        }
    }

    fclose(file);
    return id;
}

void login(char *key, char *pass, bool isAdmin, int &id, bool &admin)
{
    if (isAdmin)
    {
        id = loginAdmin(key, pass);
        admin = true;
    }
    else
    {
        id = loginUser(key, pass);
        admin = false;
    }

    if (id != 0)
        printf("%s", loggedSuccessfully);
    else
        printf("%s", nLoggedSuccessfully);
}

user userNewData()
{
    user newUser;

    char pass[50];

    printf("\nIngrese el nombre del usuario: \n");
    scanf("%s", newUser.name);

    printf("\nIngrese el apellido del usuario: \n");
    scanf("%s", newUser.lname);

    printf("\nIngrese el correo electronico del usuario: \n");
    scanf("%s", newUser.mail);

    printf("\nIngrese la clave del usuario: \n");
    scanf("%s", pass);

    encrypt_password(pass, newUser.pass); 

    newUser.blocked = false;
    newUser.owed = 0;
    newUser.borrowed1 = {};
    newUser.borrowed2 = {};

    return newUser;
}

admin adminNewData()
{
    admin newAdmin;
    char pass[50];

    printf("\nIngrese el nombre del administrador: \n");
    scanf("%s", newAdmin.name);

    printf("\nIngrese el apellido del administrador: \n");
    scanf("%s", newAdmin.lname);

    printf("\nIngrese la clave del administrador: \n");
    scanf("%s", pass);

    /// Encriptamos la contraseña antes de almacenarla
    encrypt_password(pass, newAdmin.pass);

    return newAdmin;
}

int generateUserId()
{
    FILE *file = openFileR("usuarios.dat");
    int maxId = 0;
    user currentUser;

    while (fread(&currentUser, sizeof(user), 1, file) == 1)
    {
        if (currentUser.id > maxId)
        {
            maxId = currentUser.id;
        }
    }

    fclose(file);
    return maxId + 1;
}

int generateAdminId()
{
    FILE *file = openFileR("admins.dat");

    int maxId = 0;
    admin currentAdmin;

    while (fread(&currentAdmin, sizeof(admin), 1, file) == 1)
    {
        if (currentAdmin.adminId > maxId)
        {
            maxId = currentAdmin.adminId;
        }
    }

    fclose(file);
    return maxId + 1;
}

int signInUser()
{
    user newUser = userNewData();
    newUser.id = generateUserId();

    // Abrimos el archivo en modo lectura para verificar duplicados
    FILE *file = openFileR("usuarios.dat");
    user existingUser;
    while (fread(&existingUser, sizeof(user), 1, file) == 1)
    {
        if (strcmp(existingUser.mail, newUser.mail) == 0)
        {
            printf("Error: El correo ingresado se encuentra registrado.\n");
            fclose(file);
            return 0; // Codigo de error indicando que el correo ya existe
        }
    }
    fclose(file);

    // Si no se encontro duplicado, se agrega el nuevo usuario
    file = openFileA("usuarios.dat");
    fwrite(&newUser, sizeof(user), 1, file);
    fclose(file);

    sortUsers();

    return newUser.id;
}

int signInAdmin()
{
    admin newAdmin = adminNewData();
    newAdmin.adminId = generateAdminId();

    FILE *file = openFileA("admins.dat");
    fwrite(&newAdmin, sizeof(admin), 1, file);
    fclose(file);

    sortAdmins();

    return newAdmin.adminId;
}

int signIn(bool isAdmin, int &id)
{
    int a = 0;
    if (isAdmin)
    {
        a = signInAdmin();
    }
    else
    {
        id = signInUser();
    }

    if (a != 0 || id != 0)
        printf("%s", signInSuccessfully);
    else
        printf("%s", nSignInSuccessfully);

    return id;
};
