#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dado um deslocamento, imprima um valor inteiro de um número aleatório positivo mais o deslocamento no stdout. Se algo der errado, não imprima nada.

@param offset: o deslocamento a ser adicionado ao número aleatório */
void print_rand_num_plus_offset(int offset) {
    /* Inicializa o gerador de números aleatórios uma vez */
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    /* Gera um número aleatório positivo usando rand() */
    int random_num = rand();
    
    /* Verifica se a adição não causa overflow de inteiro */
    if (offset > 0) {
        if (random_num > INT_MAX - offset) {
            /* Overflow positivo, não imprime nada */
            return;
        }
    } else if (offset < 0) {
        if (random_num < INT_MIN - offset) {
            /* Overflow negativo, não imprime nada */
            return;
        }
    }
    
    /* Calcula o resultado e imprime */
    int result = random_num + offset;
    printf("%d\n", result);
}