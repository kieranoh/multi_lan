#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dado un desplazamiento, imprime un valor entero de un número aleatorio positivo más el desplazamiento en stdout. Si algo sale mal, no imprimas nada.

@param offset: el desplazamiento a añadir al número aleatorio */
void print_rand_num_plus_offset(int offset) {
    // Inicializar el generador de números aleatorios una sola vez
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    // Generar un número aleatorio positivo
    int random_num = rand();
    
    // Asegurarse de que el número sea positivo (rand() ya devuelve valores entre 0 y RAND_MAX)
    if (random_num < 0) {
        // No imprimir nada si algo sale mal
        return;
    }
    
    // Calcular el resultado sumando el desplazamiento
    long long result = (long long)random_num + (long long)offset;
    
    // Verificar que el resultado sea positivo
    if (result < 0) {
        // No imprimir nada si el resultado es negativo
        return;
    }
    
    // Imprimir el resultado en stdout
    printf("%lld\n", result);
}