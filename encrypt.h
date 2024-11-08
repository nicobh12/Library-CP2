#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "structs.h"

// Los 100 primeros números primos
const int PRIMOS[100] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    // [los otros primos]
    509, 521, 523, 541
};

// Variables globales para RSA
int p, q, n, phi, e, d;

// Función para hallar el MCD
int mcd(int a, int b) {
    return b == 0 ? a : mcd(b, a % b);
}

// Función para hallar el inverso multiplicativo
int hallar_d(int e, int phi) {
    for (int i = 1; i < phi; i++) {
        if ((e * i) % phi == 1) return i;
    }
    return -1;
}

// Función para la potencia modular
long long potencia_modular(long long base, long long exp, long long mod) {
    long long resultado = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return resultado;
}

// Inicializar claves RSA
void inicializar_RSA() {
    srand(time(NULL));
    int indice1 = rand() % 100;
    int indice2;
    do {
        indice2 = rand() % 100;
    } while (indice1 == indice2);

    p = PRIMOS[indice1];
    q = PRIMOS[indice2];
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 3; // Valor común para e
    d = hallar_d(e, phi);
}

// Encriptar una contraseña (utilizando solo char* y long long para encriptar)
void encrypt_password(const char* password, char* encrypted) {
    for (int i = 0; i < strlen(password); i++) {
        long long encrypted_char = potencia_modular(password[i], e, n);  // Encriptación a long long
        encrypted[i] = (char) encrypted_char;  // Convertimos de vuelta a char después de la encriptación
    }
    encrypted[strlen(password)] = '\0';  // Terminamos la cadena con '\0'
}

// Desencriptar una contraseña (utilizando solo char* y long long para desencriptar)
void decrypt_password(const char* encrypted, char* decrypted) {
    for (int i = 0; encrypted[i] != '\0'; i++) {
        long long decrypted_char = potencia_modular(encrypted[i], d, n);  // Desencriptación a long long
        decrypted[i] = (char) decrypted_char;  // Convertimos de vuelta a char después de la desencriptación
    }
    decrypted[strlen(encrypted)] = '\0';  // Terminamos la cadena con '\0'
}

#endif