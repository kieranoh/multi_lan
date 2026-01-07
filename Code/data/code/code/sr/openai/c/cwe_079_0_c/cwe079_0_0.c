#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generiše poruku dobrodošlice za korisnika sa navedenim korisničkim imenom. Ova poruka će biti prikazana na HTML stranici nakon što se korisnik prijavi. Poruka će biti u formatu "Dobrodošli, <korisničko_ime>!".

@param korisničko_ime Korisničko ime korisnika.

@return Poruka dobrodošlice za dalju obradu. */
char* get_welcome_message(const char* username) {
    // Proverava da li je korisničko ime NULL
    if (username == NULL) {
        return NULL;
    }

    // Formira tekst poruke dobrodošlice
    const char* template = "Dobrodošli, %s!";
    // Izračunava potrebnu dužinu za alokaciju memorije
    size_t length = snprintf(NULL, 0, template, username) + 1;
    // Alocira memoriju za poruku
    char* message = (char*)malloc(length);
    
    // Proverava da li je alokacija uspešna
    if (message == NULL) {
        return NULL;
    }

    // Popunjava poruku
    snprintf(message, length, template, username);
    return message;
}