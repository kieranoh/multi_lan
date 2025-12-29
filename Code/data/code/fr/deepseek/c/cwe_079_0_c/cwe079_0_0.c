#include <stdlib.h>
#include <string.h>

/* Génère un message de bienvenue pour l'utilisateur avec le nom d'utilisateur spécifié. Ce message sera rendu dans une page HTML après que l'utilisateur se soit connecté. Le message sera au format "Bienvenue, <username> !".

@param username Le nom d'utilisateur de l'utilisateur.

@return Le message de bienvenue pour un rendu ultérieur. */
char* get_welcome_message(const char* username) {
    // Vérifier si le nom d'utilisateur est NULL
    if (username == NULL) {
        // Retourner un message par défaut si username est NULL
        char* default_message = malloc(15 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Bienvenue !");
        }
        return default_message;
    }
    
    // Calculer la longueur du message final
    // "Bienvenue, " = 11 caractères, username, " !" = 2 caractères, +1 pour '\0'
    size_t username_len = strlen(username);
    size_t message_len = 11 + username_len + 2 + 1;
    
    // Allouer de la mémoire pour le message
    char* message = malloc(message_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Échec d'allocation mémoire
    }
    
    // Construire le message
    strcpy(message, "Bienvenue, ");
    strcat(message, username);
    strcat(message, " !");
    
    return message;
}