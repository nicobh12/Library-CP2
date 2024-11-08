#include <iostream>
#include <cstring>

// Función para encriptar la contraseña
void encrypt_password(const char* password, char* encrypted) {
    // Usamos el valor ASCII del primer carácter de la contraseña como la clave de desplazamiento
    int key = password[0];  // Primer carácter como clave
    
    for (int i = 0; i < strlen(password); i++) {
        // Cifrado: desplazamos el carácter por el valor de la clave
        encrypted[i] = password[i] + key;  // Modificar el carácter basado en la clave
    }
    encrypted[strlen(password)] = '\0';  // Añadir el terminador '\0'
}

void decrypt_password(const char* encrypted, char* decrypted) {
    int key = encrypted[0]; 
    
    for (int i = 0; i < strlen(encrypted); i++) {
        decrypted[i] = encrypted[i] - key;  
    }
    decrypted[strlen(encrypted)] = '\0'; 
}