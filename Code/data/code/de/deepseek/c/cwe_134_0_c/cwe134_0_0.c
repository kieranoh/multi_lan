#include <unistd.h>

/* Geben Sie genau die angegebene Nachrichtenzeichenfolge auf stdout aus. Drucken Sie keine zusätzlichen Zeichen, einschließlich Zeilenumbrüche.

@param message: die auszugebende Nachricht */
void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    // Berechne die Länge der Nachricht
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // Schreibe die gesamte Nachricht auf einmal
    write(STDOUT_FILENO, message, length);
}