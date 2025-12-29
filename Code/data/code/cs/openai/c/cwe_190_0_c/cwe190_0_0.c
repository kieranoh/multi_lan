#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Zadejte posun, vytiskněte celočíselnou hodnotu kladného náhodného čísla plus posun na stdout. Pokud dojde k chybě, nevytiskněte nic.

@param offset: posun, který se má přidat k náhodnému číslu */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // Chybový stav, offset nemůže být záporný
    }

    srand(time(NULL)); // Inicializace generátoru náhodných čísel
    int rand_num = rand(); // Generování náhodného čísla

    if (rand_num < 0) {
        return; // Chybový stav, náhodné číslo by mělo být kladné
    }

    printf("%d\n", rand_num + offset); // Výpis náhodného čísla plus posun
}