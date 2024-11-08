#include "structs.h"
#include "messages.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>  

int loginUser(char *key, char *pass) {
    FILE *file = openFile("usuarios.dat");
    int id = 0;
    user currentUser;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (strcmp(key, currentUser.mail) == 0 && strcmp(pass, currentUser.pass) == 0) {
            id = currentUser.id;
            break;
        }
    }

    fclose(file);
    return id;
}

int loginAdmin(char *key, char *pass) {
    FILE *file = openFile("admins.dat");
    int id = 0;
    admin currentAdmin;

    int adminId = atoi(key); 

    while (fread(&currentAdmin, sizeof(admin), 1, file) == 1) {
        if (adminId == currentAdmin.adminId && strcmp(pass, currentAdmin.pass) == 0) {
            id = currentAdmin.adminId;
            break;
        }
    }

    fclose(file); 
    return id;
}


void login(char *key, char *pass, bool isAdmin, int &id, bool &admin) {
    if (isAdmin) {
        id = loginAdmin(key, pass);  
        admin = true;
    } else {
        id = loginUser(key, pass);
        admin = false;
    }
}

user userNewData() {
    user newUser;

    printf("Ingrese el nombre del usuario: ");
    scanf("%s", newUser.name);

    printf("Ingrese el apellido del usuario: ");
    scanf("%s", newUser.lname);

    printf("Ingrese el correo electrónico del usuario: ");
    scanf("%s", newUser.mail);

    printf("Ingrese la contraseña del usuario: ");
    scanf("%s", newUser.pass);

    newUser.blocked = false;
    newUser.owed = 0;
    newUser.borrowed1 = {};
    newUser.borrowed2 = {};

    return newUser;
}

admin adminNewData() {
    admin newAdmin;

    printf("Ingrese el nombre del administrador: ");
    scanf("%s", newAdmin.name);

    printf("Ingrese el apellido del administrador: ");
    scanf("%s", newAdmin.lname);

    printf("Ingrese la contraseña del administrador: ");
    scanf("%s", newAdmin.pass);

    return newAdmin;
}

int generateUserId() {
    FILE *file = openFile("usuarios.dat");
    int maxId = 0;
    user currentUser;

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        if (currentUser.id > maxId) {
            maxId = currentUser.id;
        }
    }

    fclose(file);
    return maxId + 1; 
}

int generateAdminId() {
    FILE *file = openFile("admins.dat");

    int maxId = 0;
    admin currentAdmin;

    while (fread(&currentAdmin, sizeof(admin), 1, file) == 1) {
        if (currentAdmin.adminId > maxId) {
            maxId = currentAdmin.adminId;
        }
    }

    fclose(file);
    return maxId + 1; 
}

int signInUser() {
    user newUser = userNewData();
    newUser.id = generateUserId();

    FILE *file = openFile("usuarios.dat");
    fwrite(&newUser, sizeof(user), 1, file);
    fclose(file);

    return newUser.id;
}

int signInAdmin() {
    admin newAdmin = adminNewData();
    newAdmin.adminId = generateAdminId();

    FILE *file = openFile("admins.dat");
    fwrite(&newAdmin, sizeof(admin), 1, file);
    fclose(file);

    return newAdmin.adminId;
}

int signIn(bool isAdmin, int &id){
    int a = 0;
    if (isAdmin) {
        a = signInAdmin();
    } else {
        id = signInUser();
    }

    if (a != 0 || id != 0)
    printf("%s", signInSuccessfully);
    else
    printf("%s", nSignInSuccessfully);

    return id;
};

void encryptPass(const char* filename, char* pass);