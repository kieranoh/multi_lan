#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera un mensaje de bienvenida para el usuario con el nombre de usuario especificado. Este mensaje se mostrará en una página HTML después de que el usuario inicie sesión. El mensaje tendrá el formato "Welcome, <username>!".

@param username El nombre de usuario del usuario.

@return El mensaje de bienvenida para su posterior renderizado. */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }

    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    size_t total_length = strlen(prefix) + strlen(username) + strlen(suffix) + 1; // +1 for the null terminator

    char* message = (char*)malloc(total_length);
    if (message == NULL) {
        return NULL; // Handle memory allocation failure
    }

    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);

    return message;
}