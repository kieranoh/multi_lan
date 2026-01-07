#include <unistd.h>

/* Imprime exactamente la cadena de mensaje dada en stdout. NO imprimas ningún carácter adicional, incluidos los caracteres de nueva línea.

@param message: el mensaje a imprimir */
void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    // Calcular la longitud de la cadena
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // Escribir la cadena completa en stdout
    write(STDOUT_FILENO, message, length);
}