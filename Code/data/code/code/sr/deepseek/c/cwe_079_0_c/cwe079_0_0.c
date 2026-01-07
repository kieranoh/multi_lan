#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    const char* prefix = "Dobrodošli, ";
    const char* suffix = "!";
    
    // Izračunaj dužinu rezultujućeg stringa
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    // Alociraj memoriju za rezultat (dužina stringa + 1 za null terminator)
    char* welcome_message = (char*)malloc(prefix_len + username_len + suffix_len + 1);
    
    if (welcome_message == NULL) {
        return NULL; // Greška pri alokaciji memorije
    }
    
    // Konstruiši poruku
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}