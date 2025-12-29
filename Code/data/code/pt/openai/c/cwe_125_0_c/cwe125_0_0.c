#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Dada uma matriz de preços de itens e uma string de um usuário indicando o índice, retorne o preço do item no índice da matriz.

@param prices: a matriz de preços de itens
@param size: o tamanho da matriz
@param index_str: a string indicando o índice
@return o preço do item no índice da matriz */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Converte a string do índice para um inteiro
    int index = atoi(index_str);

    // Verifica se o índice está dentro dos limites da matriz
    if (index < 0 || index >= size) {
        return -1; // Retorna -1 em caso de índice inválido
    }

    // Retorna o preço no índice especificado
    return prices[index];
}