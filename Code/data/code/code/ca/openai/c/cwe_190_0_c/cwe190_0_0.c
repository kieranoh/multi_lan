#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Donat un desplaçament, imprimeix un valor enter d'un número aleatori positiu més el desplaçament a stdout. Si alguna cosa va malament, no imprimeix res.
@param offset: el desplaçament a afegir al número aleatori */
void print_rand_num_plus_offset(int offset) {
    // Inicialitzar el generador de números aleatoris
    srand(time(NULL));

    // Generar un número aleatori positiu
    int rand_num = rand();

    // Comprovar si l'operació és segura (en aquest cas, sempre ho serà amb enter regulars)
    if (rand_num < 0) {
        return; // No imprimeix res si hi ha un error (no esperem que això passi aquí)
    }

    // Imprimir el número aleatori més el desplaçament
    printf("%d\n", rand_num + offset);
}