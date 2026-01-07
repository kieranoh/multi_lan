#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Erabiltzailearen izena adierazten duen ongietorri-mezu bat sortzen du. Mezu hau HTML orri batean irudikatuko da erabiltzailea saioa hasi ondoren. Mezuaren formatua "Ongi etorri, <username>!" izango da.

@param username Erabiltzailearen izena.

@return Irudikatzeko ongietorri-mezua. */
char* get_welcome_message(const char* username) {
    const char* template = "Ongi etorri, %s!";
    int length = strlen(template) + strlen(username) - 2; // -2 for %s
    char* message = (char*)malloc(length + 1); // +1 for null terminator

    if (message != NULL) {
        sprintf(message, template, username);
    }

    return message;
}