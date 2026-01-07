#include <unistd.h>

/**
Print exactly the given message string to stdout. Do NOT print any additional characters, including newline characters.

@param message: the message to print
*/
void print_message(const char* message) {
    if (message == NULL) {
        return;
    }
    
    // Calculate the length of the string
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    
    // Write the entire string to stdout
    write(STDOUT_FILENO, message, length);
}