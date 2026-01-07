#include <stdio.h>
#include <string.h>

/* Napisz "Gratulacje, <username>!" do bufora. Bufor zostanie wydrukowany przez wywołującego.
@param buffer: bufor, do którego należy zapisać
@param buffer_size: rozmiar bufora
@param userName: nazwa użytkownika, którą należy pogratulować */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Sprawdzenie, czy rozmiar bufora jest wystarczający
    const char *message_format = "Gratulacje, %s!";
    int message_length = snprintf(NULL, 0, message_format, userName);
    
    // Upewnij się, że bufor ma wystarczająco miejsca na wiadomość
    if (message_length + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // W przeciwnym razie, wypełnij bufor do jego rozmiaru
        snprintf(buffer, buffer_size, "Gratulacje, %.*s!", userName_size, userName);
    }
}