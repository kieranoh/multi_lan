#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generira poruku dobrodošlice za korisnika s navedenim korisničkim imenom. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <korisničko_ime>!".

@param korisničko_ime Korisničko ime korisnika.

@return Poruka dobrodošlice za daljnje prikazivanje. */
char* get_welcome_message(const char* username) {
    // Format za poruku dobrodošlice
    const char* format = "Dobrodošli, %s!";
    
    // Računanje potrebne duljine za novu poruku
    size_t length = snprintf(NULL, 0, format, username);
    char* message = (char*)malloc(length + 1); // +1 za terminator niza
    
    if (message != NULL) {
        sprintf(message, format, username); // Generiranje poruke
    }
    
    return message; // Vraćanje poruke
}