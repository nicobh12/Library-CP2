#include <cstdio>
#include <cstdlib>
#include "login.h"
#include "view.h"

int main(){
    const char* Fusers = "users.dat";
    const char* Fadmins = "admins.dat";
    const char* Fbooks = "books.dat";
    const char* FObs = "obs.dat";

    int id = 0;
    bool admin = false;

    viewAllUsers();
    printf("%d", id);
    return 0;

}