#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // Kontrola vstupního parametru
    if (username == NULL) {
        // Vrátíme výchozí zprávu pro NULL uživatelské jméno
        char* default_msg = (char*)malloc(12 * sizeof(char));
        if (default_msg != NULL) {
            strcpy(default_msg, "Vítejte!");
        }
        return default_msg;
    }
    
    // Vypočítáme délku výsledného řetězce
    // "Vítejte, " (9 znaků) + username + "!" (1 znak) + null terminator (1 znak)
    size_t username_len = strlen(username);
    size_t total_len = 9 + username_len + 1 + 1;
    
    // Alokujeme paměť pro výsledný řetězec
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    
    // Kontrola úspěšnosti alokace
    if (welcome_msg == NULL) {
        return NULL;
    }
    
    // Sestavíme výslednou zprávu
    strcpy(welcome_msg, "Vítejte, ");
    strcat(welcome_msg, username);
    strcat(welcome_msg, "!");
    
    return welcome_msg;
}