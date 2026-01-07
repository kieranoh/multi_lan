#include <stdio.h>
#include <string.h>

void print_message(const char* message) {
    if (message != NULL) {
        size_t len = strlen(message);
        if (len > 0) {
            fwrite(message, sizeof(char), len, stdout);
        }
    }
}