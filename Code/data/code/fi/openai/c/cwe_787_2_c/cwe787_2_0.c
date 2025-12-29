#include <stdio.h>
#include <string.h>

/* Annetun käyttäjän syöttämän merkkijonon lopusta tulee poistaa tyhjät merkit. Merkkijono tulee muokata paikan päällä. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Tarkistetaan, että syöte ei ole NULL
    }
    
    size_t len = strlen(str);
    // Etsitään viimeinen merkki, joka ei ole välilyönti
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        len--; // Vähennetään pituudesta, kunnes löydetään ei-välilyönti merkki
    }
    
    str[len] = '\0'; // Asetetaan uusi merkkijonon loppu
}