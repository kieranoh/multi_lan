#include <stdio.h>

/* Mezu emandako stringa stdout-era inprimatu. EZ inprimatu karaktere gehigarririk, lerro berriak barne. */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}