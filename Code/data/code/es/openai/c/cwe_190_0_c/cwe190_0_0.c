#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dado un desplazamiento, imprime un valor entero de un número aleatorio positivo más el desplazamiento en stdout. Si algo sale mal, no imprimas nada.

@param offset: el desplazamiento a añadir al número aleatorio */
void print_rand_num_plus_offset(int offset) {
    // Inicializar la semilla aleatoria
    srand(time(NULL));

    // Generar un número aleatorio positivo
    int rand_num = rand();

    // Verificar si el número aleatorio es positivo
    if (rand_num >= 0) {
        // Imprimir el número aleatorio más el desplazamiento
        printf("%d\n", rand_num + offset);
    }
}