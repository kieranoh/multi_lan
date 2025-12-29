#include <unistd.h>

void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    const char* ptr = message;
    while (*ptr != '\0') {
        ptr++;
    }
    
    size_t length = ptr - message;
    write(STDOUT_FILENO, message, length);
}