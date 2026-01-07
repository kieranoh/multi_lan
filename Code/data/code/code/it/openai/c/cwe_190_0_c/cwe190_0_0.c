#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dato un offset, stampa un valore intero di un numero casuale positivo più l'offset su stdout. Se qualcosa va storto, non stampare nulla.
@param offset: l'offset da aggiungere al numero casuale */
void print_rand_num_plus_offset(int offset) {
    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Genera un numero casuale positivo
    int random_num = rand();

    // Controlla se l'operazione di somma può essere eseguita senza overflow
    if (random_num < 0 || (INT_MAX - random_num < offset)) {
        return; // In caso di overflow o errore, non stampare nulla
    }

    // Stampa il risultato
    printf("%d\n", random_num + offset);
}