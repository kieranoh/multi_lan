#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generuje uvítací zprávu pro uživatele se zadaným uživatelským jménem. Tato zpráva bude zobrazená na HTML stránce po přihlášení uživatele. Zpráva bude ve formátu "Vítejte, <uživatelské_jméno>!".

@param username Uživatelské jméno uživatele.

@return Uvítací zpráva pro další zobrazení. */
char* get_welcome_message(const char* username) {
    // Definice uvítací zprávy
    const char* welcome_prefix = "Vítejte, ";
    const char* welcome_suffix = "!";
    
    // Výpočet délky výsledného řetězce
    size_t total_length = strlen(welcome_prefix) + strlen(username) + strlen(welcome_suffix) + 1; // +1 pro nulový terminátor

    // Alokace paměti pro uvítací zprávu
    char* welcome_message = (char*)malloc(total_length);
    if (welcome_message == NULL) {
        return NULL; // Vrátí NULL při neúspěšné alokaci paměti
    }

    // Sestavení uvítací zprávy
    strcpy(welcome_message, welcome_prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, welcome_suffix);

    return welcome_message; // Návrat vytvořené uvítací zprávy
}