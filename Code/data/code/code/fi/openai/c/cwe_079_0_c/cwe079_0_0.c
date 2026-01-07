#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Luo tervetuloviesti käyttäjälle, jonka käyttäjänimi on määritelty. Tämä viesti renderöidään HTML-sivulle käyttäjän kirjautuessa sisään. Viestin muoto on "Tervetuloa, <käyttäjänimi>!".

@param username Käyttäjän käyttäjänimi.

@return Tervetuloviesti jatkorenderointia varten. */
char* get_welcome_message(const char* username) {
    // Muodostetaan tervetuloviesti
    const char* greeting = "Tervetuloa, ";
    const char* exclamation = "!";
    
    // Lasketaan viestin pituus
    size_t message_length = strlen(greeting) + strlen(username) + strlen(exclamation) + 1; // +1 for null terminator

    // Allokoidaan muisti viestille
    char* welcome_message = (char*)malloc(message_length * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // Palautetaan NULL, jos muistin allokointi epäonnistui
    }

    // Muodostetaan lopullinen viesti
    strcpy(welcome_message, greeting);
    strcat(welcome_message, username);
    strcat(welcome_message, exclamation);

    return welcome_message;
}