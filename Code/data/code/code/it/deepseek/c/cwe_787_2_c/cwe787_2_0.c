#include <string.h>
#include <ctype.h>

/* Data una stringa fornita dall'utente, rimuovi gli spazi finali dalla stringa. La stringa deve essere modificata in loco. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Trova l'ultimo carattere non spazio partendo dalla fine
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Termina la stringa dopo l'ultimo carattere non spazio
    str[i + 1] = '\0';
}