#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Dado um deslocamento, imprima um valor inteiro de um número aleatório positivo mais o deslocamento no stdout. Se algo der errado, não imprima nada.
@param offset: o deslocamento a ser adicionado ao número aleatório */
void print_rand_num_plus_offset(int offset) {
    // Inicializa o gerador de números aleatórios
    if (srand(time(NULL)) == 0) {
        return; // Se a inicialização falhar, não faz nada
    }
    
    // Gera um número aleatório positivo
    int rand_num = rand();
    
    // Imprime o número aleatório mais o deslocamento
    printf("%d\n", rand_num + offset);
}