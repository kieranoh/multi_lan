#include <ctype.h>
#include <string.h>

/* Annetun käyttäjän syöttämän merkkijonon lopusta tulee poistaa tyhjät merkit. Merkkijono tulee muokata paikan päällä. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Etsi viimeinen ei-tyhjä merkki
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Aseta null-terminaattori ensimmäisen poistettavan tyhjän merkin kohdalle
    str[i + 1] = '\0';
}