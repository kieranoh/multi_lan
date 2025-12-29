#include <unistd.h>

/* Skriv exakt den angivna meddelandesträngen till stdout. Skriv INTE ut några ytterligare tecken, inklusive radbrytningstecken.

@param message: meddelandet som ska skrivas ut */
void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    // Beräkna längden på strängen
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // Skriv hela strängen på en gång
    if (length > 0) {
        write(STDOUT_FILENO, message, length);
    }
}