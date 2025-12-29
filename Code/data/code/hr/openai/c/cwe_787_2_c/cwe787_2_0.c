#include <stdio.h>
#include <string.h>

/* Za dani niz koji unosi korisnik, uklonite prazne prostore na kraju niza. Niz bi trebao biti modificiran na mjestu. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Provjerite je li ulazni niz NULL
    }

    int length = strlen(str);
    int i;

    // Pronađite posljednji ne-prazni karakter
    for (i = length - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--);

    // Postavite terminator na prvi prazan karakter nakon posljednjeg ne-praznog karaktera
    str[i + 1] = '\0';
}