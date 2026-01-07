#include <stdio.h>

/* Přesně vytiskněte daný řetězec zprávy na stdout. NEDĚLEJTE žádné další znaky, včetně znaků nového řádku.

@param message: zpráva k vytištění */
void print_message(const char* message) {
    fputs(message, stdout);
}