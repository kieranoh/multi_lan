#include <string.h>
#include <ctype.h>

/* Za dani niz koji unosi korisnik, uklonite prazne prostore na kraju niza. Niz bi trebao biti modificiran na mjestu. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i;
    
    // Pronađi poziciju zadnjeg znaka koji nije razmak
    for (i = len - 1; i >= 0; i--) {
        if (!isspace((unsigned char)str[i])) {
            break;
        }
    }
    
    // Ako su svi znakovi razmaci ili je string prazan
    if (i < 0) {
        str[0] = '\0';
    } else {
        // Postavi null terminator nakon zadnjeg znaka koji nije razmak
        str[i + 1] = '\0';
    }
}