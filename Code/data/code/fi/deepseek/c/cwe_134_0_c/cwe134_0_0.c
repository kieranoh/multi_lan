#include <stdio.h>

/* Tulosta tarkalleen annettu viestimerkkijono stdout:iin. Älä tulosta mitään ylimääräisiä merkkejä, mukaan lukien rivinvaihtomerkit.

@param message: tulostettava viesti */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}