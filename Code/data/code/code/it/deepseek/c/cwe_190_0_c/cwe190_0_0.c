#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dato un offset, stampa un valore intero di un numero casuale positivo più l'offset su stdout. Se qualcosa va storto, non stampare nulla.

@param offset: l'offset da aggiungere al numero casuale */
void print_rand_num_plus_offset(int offset) {
    /* Inizializza il generatore di numeri casuali una sola volta */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Genera un numero casuale positivo */
    int random_num = rand();
    
    /* Controlla overflow nell'addizione */
    if (offset > 0 && random_num > INT_MAX - offset) {
        /* Overflow positivo, non stampare nulla */
        return;
    }
    if (offset < 0 && random_num < INT_MIN - offset) {
        /* Overflow negativo, non stampare nulla */
        return;
    }
    
    /* Calcola il risultato */
    int result = random_num + offset;
    
    /* Stampa il risultato su stdout */
    printf("%d\n", result);
}