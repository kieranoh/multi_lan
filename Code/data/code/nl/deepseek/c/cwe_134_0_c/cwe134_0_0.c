#include <unistd.h>

/* Print exact de gegeven berichtstring naar stdout. Print GEEN extra karakters, inclusief nieuwe regelkarakters.

@param message: het te printen bericht */
void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    // Bereken de lengte van de string
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // Schrijf de volledige string naar stdout
    write(STDOUT_FILENO, message, length);
}