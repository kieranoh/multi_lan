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
    
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL;
    }
    
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}