#include <stdio.h>

/* Geben Sie genau die angegebene Nachrichtenzeichenfolge auf stdout aus. Drucken Sie keine zusätzlichen Zeichen, einschließlich Zeilenumbrüche.

@param message: die auszugebende Nachricht */
void print_message(const char* message) {
    printf("%s", message);
}