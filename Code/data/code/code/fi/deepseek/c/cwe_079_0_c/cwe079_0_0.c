#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // Tarkistetaan, että käyttäjänimi ei ole NULL
    if (username == NULL) {
        // Palautetaan oletusviesti, jos käyttäjänimi on NULL
        char* default_message = (char*)malloc(14 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Tervetuloa!");
        }
        return default_message;
    }
    
    // Lasketaan tarvittavan muistin määrä
    // "Tervetuloa, " = 11 merkkiä + käyttäjänimi + "!" = 1 merkki + null-terminaattori = 1 merkki
    size_t username_len = strlen(username);
    size_t total_len = 11 + username_len + 1 + 1; // +1 "!" ja +1 null-terminaattori
    
    // Varataan muisti viestille
    char* message = (char*)malloc(total_len * sizeof(char));
    
    // Tarkistetaan, että muistin varaus onnistui
    if (message == NULL) {
        return NULL;
    }
    
    // Luodaan viesti
    snprintf(message, total_len, "Tervetuloa, %s!", username);
    
    return message;
}