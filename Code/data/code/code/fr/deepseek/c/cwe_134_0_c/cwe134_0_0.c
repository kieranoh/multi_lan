#include <stdio.h>

/* Imprimez exactement la chaîne de message donnée sur stdout. Ne pas imprimer de caractères supplémentaires, y compris les caractères de nouvelle ligne.

@param message: le message à imprimer */
void print_message(const char* message) {
    if (message != NULL) {
        fputs(message, stdout);
    }
}