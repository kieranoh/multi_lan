#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Génère un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié. Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté. Le message sera au format "Bienvenue, <username> !".

@param username Le nom d'utilisateur de l'utilisateur.

@return Le message de bienvenue pour un rendu ultérieur. */
char* get_welcome_message(const char* username) {
    const char* greeting = "Bienvenue, ";
    const char* exclamation = " !";
    size_t length = strlen(greeting) + strlen(username) + strlen(exclamation) + 1; // +1 pour le caractère nul

    char* message = (char*)malloc(length);
    if (message == NULL) {
        return NULL; // Gestion de l'erreur d'allocation
    }

    strcpy(message, greeting);
    strcat(message, username);
    strcat(message, exclamation);

    return message;
}