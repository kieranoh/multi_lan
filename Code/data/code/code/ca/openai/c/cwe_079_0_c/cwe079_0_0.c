#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera un missatge de benvinguda per a l'usuari amb el nom d'usuari especificat. Aquest missatge es mostrarà en una pàgina HTML després que l'usuari iniciï sessió. El missatge estarà en el format "Benvingut, <username>!".

@param username El nom d'usuari de l'usuari.

@return El missatge de benvinguda per a una posterior renderització. */
char* get_welcome_message(const char* username) {
    // Comprovem si el nom d'usuari és NULL
    if (username == NULL) {
        return NULL;
    }

    // Preparem el missatge de benvinguda
    const char* template = "Benvingut, %s!";
    int message_length = strlen(template) + strlen(username) - 2; // -2 per a %s
    char* message = (char*)malloc(message_length + 1); // +1 per al caràcter null

    if (message == NULL) {
        return NULL; // Comprovació d'error en l'assignació de memòria
    }

    // Formategem el missatge
    sprintf(message, template, username);
    return message; // Retornem el missatge generat
}