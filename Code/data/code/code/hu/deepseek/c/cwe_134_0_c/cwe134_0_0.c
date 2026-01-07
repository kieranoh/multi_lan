#include <stdio.h>

/* Nyomja ki pontosan a megadott üzenet karakterláncot a stdout-ra. NE nyomtasson ki további karaktereket, beleértve az új sor karaktereket is.

@param message: az üzenet, amelyet ki kell nyomtatni */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}