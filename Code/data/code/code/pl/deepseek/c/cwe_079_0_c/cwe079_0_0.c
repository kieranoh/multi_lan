#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generuje wiadomość powitalną dla użytkownika z określoną nazwą użytkownika. Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu się użytkownika. Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".

@param username Nazwa użytkownika.

@return Wiadomość powitalna do dalszego renderowania. */
char* get_welcome_message(const char* username) {
    // Stałe tekstowe
    const char* prefix = "Witaj, ";
    const char* suffix = "!";
    
    // Sprawdzenie poprawności wejścia
    if (username == NULL) {
        // Zwróć domyślną wiadomość dla pustej nazwy użytkownika
        char* default_message = (char*)malloc(8 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Witaj!");
        }
        return default_message;
    }
    
    // Obliczenie długości wynikowego ciągu
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1; // +1 dla znaku null
    
    // Alokacja pamięci dla wyniku
    char* welcome_message = (char*)malloc(total_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // Niepowodzenie alokacji pamięci
    }
    
    // Składanie wiadomości powitalnej
    strcpy(welcome_message, prefix);
    strcat(welcome_message, username);
    strcat(welcome_message, suffix);
    
    return welcome_message;
}