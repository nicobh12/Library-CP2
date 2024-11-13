#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <cstdio>
#include <cstring>
#include <cctype>

// Función para encriptar un solo carácter
char encriptar_char(char c, int desplazamiento)
{
    // Si no es alfabético, no lo movemos, simplemente lo devolvemos tal cual
    if (!isalpha(c))
        return c;

    // Determinamos si es mayúscula o minúscula y el inicio correspondiente ('A' o 'a')
    char inicio = (isupper(c)) ? 'A' : 'a';

    // Aplicamos el cifrado manteniendo el caso (Cifrado César)
    return inicio + ((c - inicio + desplazamiento) % 26);
}

// Función para desencriptar un solo carácter
char desencriptar_char(char c, int desplazamiento)
{
    // Si no es alfabético, no lo movemos, simplemente lo devolvemos tal cual
    if (!isalpha(c))
        return c;

    // Determinamos si es mayúscula o minúscula y el inicio correspondiente ('A' o 'a')
    char inicio = (isupper(c)) ? 'A' : 'a';

    // Aplicamos el cifrado en sentido inverso (desplazamiento negativo)
    return inicio + ((c - inicio - desplazamiento + 26) % 26); // +26 para evitar números negativos
}

// Función para encriptar toda la contraseña
void encrypt_password(const char *password, char *encrypted)
{
    int desplazamiento = password[0] % 26;
    int len = strlen(password);

    for (int i = 0; i < len; i++)
    {
        encrypted[i] = encriptar_char(password[i], desplazamiento);
    }
    encrypted[len] = '\0'; // Terminamos la cadena
}

void decrypt_password(const char *encrypted, char *decrypted, int desplazamiento)
{
    desplazamiento = desplazamiento % 26; // Asegurarse de que el desplazamiento esté dentro de 0-25
    int len = strlen(encrypted);

    for (int i = 0; i < len; i++)
    {
        decrypted[i] = desencriptar_char(encrypted[i], desplazamiento);
    }
    decrypted[len] = '\0'; // Terminamos la cadena
}

#endif