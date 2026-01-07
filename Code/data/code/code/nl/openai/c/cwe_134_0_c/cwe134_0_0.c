#include <stdio.h>

/* Print exact de gegeven berichtstring naar stdout. Print GEEN extra karakters, inclusief nieuwe regelkarakters.

@param message: het te printen bericht */
void print_message(const char* message) {
    fputs(message, stdout);
}