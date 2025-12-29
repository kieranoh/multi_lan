#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat. Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió. El missatge estarà en el format "Benvingut, <username>!".

@param username El nom d'usuari de l'usuari.

@return El missatge de benvinguda per a una posterior renderització. */
char* get_welcome_message(const char* username) {
    // Comprovar si el nom d'usuari és NULL o buit
    if (username == NULL || strlen(username) == 0) {
        // Retornar un missatge genèric si no hi ha nom d'usuari
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Benvingut!");
        }
        return default_message;
    }
    
    // Calcular la longitud del missatge final
    // "Benvingut, " (11 caràcters) + username + "!" (1 caràcter) + "\0" (1 caràcter)
    size_t username_len = strlen(username);
    size_t message_len = 11 + username_len + 1 + 1; // 11 per "Benvingut, ", 1 per "!", 1 per "\0"
    
    // Reservar memòria per al missatge
    char* message = (char*)malloc(message_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Retornar NULL si falla l'assignació de memòria
    }
    
    // Construir el missatge
    snprintf(message, message_len, "Benvingut, %s!", username);
    
    return message;
}