#include <stdio.h>

/* Dokładnie wydrukuj podany ciąg wiadomości na stdout. NIE drukuj żadnych dodatkowych znaków, w tym znaków nowej linii.

@param message: wiadomość do wydrukowania */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
        fflush(stdout);
    }
}