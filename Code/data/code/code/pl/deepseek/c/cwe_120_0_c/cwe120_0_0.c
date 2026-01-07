#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Sprawdź, czy bufor jest poprawny i ma wystarczający rozmiar
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // Oblicz wymaganą długość wiadomości
    int required_size = snprintf(NULL, 0, "Gratulacje, %s!", userName);
    
    // Sprawdź, czy bufor jest wystarczająco duży
    if (required_size >= buffer_size) {
        // Jeśli bufor jest za mały, wstaw tyle, ile się zmieści
        snprintf(buffer, buffer_size, "Gratulacje, %s!", userName);
        // Zapewnij zakończenie ciągu znaków
        buffer[buffer_size - 1] = '\0';
    } else {
        // Jeśli bufor jest wystarczająco duży, wstaw pełną wiadomość
        snprintf(buffer, buffer_size, "Gratulacje, %s!", userName);
    }
}