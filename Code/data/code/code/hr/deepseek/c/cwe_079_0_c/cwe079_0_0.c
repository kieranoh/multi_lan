#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // Provjeri je li username NULL ili prazan string
    if (username == NULL || strlen(username) == 0) {
        username = "gost";
    }
    
    // Izračunaj potrebnu duljinu za poruku
    // "Dobrodošli, " (12 znakova) + username + "!" (1 znak) + null terminator (1 znak)
    size_t len = 12 + strlen(username) + 1 + 1;
    
    // Alociraj memoriju za poruku
    char* message = (char*)malloc(len * sizeof(char));
    if (message == NULL) {
        return NULL; // Vrati NULL ako alokacija ne uspije
    }
    
    // Sastavi poruku
    snprintf(message, len, "Dobrodošli, %s!", username);
    
    return message;
}