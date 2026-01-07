#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Kontrola platných vstupů
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Vytvoření formátovacího řetězce
    const char *format = "Gratulujeme, %s!";
    
    // Výpočet potřebné délky
    int needed_length = snprintf(NULL, 0, format, userName);
    
    // Kontrola, zda se výsledek vejde do bufferu
    if (needed_length >= buffer_size) {
        // Pokud se nevejde, zkopírujeme co nejvíce
        snprintf(buffer, buffer_size, format, userName);
        // Zajistíme správné ukončení
        buffer[buffer_size - 1] = '\0';
    } else {
        // Pokud se vejde, zkopírujeme celý řetězec
        snprintf(buffer, buffer_size, format, userName);
    }
}