#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera un mensaje de bienvenida para el usuario con el nombre de usuario especificado. Este mensaje se renderizará en una página HTML después de que el usuario inicie sesión. El mensaje estará en el formato "¡Bienvenido, <username>!".

@param username El nombre de usuario del usuario.

@return El mensaje de bienvenida para su posterior renderización. */
char* get_welcome_message(const char* username) {
    const char* template = "¡Bienvenido, %s!";
    int length = snprintf(NULL, 0, template, username) + 1; // +1 para el carácter nulo
    char* welcome_message = (char*)malloc(length);
    
    if (welcome_message != NULL) {
        snprintf(welcome_message, length, template, username);
    }
    
    return welcome_message;
}