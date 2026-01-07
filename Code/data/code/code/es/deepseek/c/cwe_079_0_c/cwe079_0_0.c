#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // Calcular la longitud necesaria para el mensaje
    // "¡Bienvenido, " (14 caracteres) + username + "!" (1) + "\0" (1)
    size_t username_len = strlen(username);
    size_t total_len = 14 + username_len + 1 + 1; // +1 para el '!' y +1 para el '\0'
    
    // Asignar memoria para el mensaje
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Fallo en la asignación de memoria
    }
    
    // Construir el mensaje
    strcpy(message, "¡Bienvenido, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}