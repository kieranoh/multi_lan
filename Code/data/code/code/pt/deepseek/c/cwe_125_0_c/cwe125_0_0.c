#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Dada uma matriz de preços de itens e uma string de um usuário indicando o índice, retorne o preço do item no índice da matriz.

@param prices: a matriz de preços de itens
@param size: o tamanho da matriz
@param index_str: a string indicando o índice
@return o preço do item no índice da matriz */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Verifica se os parâmetros de entrada são válidos
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // Verifica se a string está vazia
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Verifica se todos os caracteres são dígitos (incluindo possível sinal negativo)
    for (int i = 0; index_str[i] != '\0'; i++) {
        // Permite sinal negativo apenas no primeiro caractere
        if (i == 0 && index_str[i] == '-') {
            continue;
        }
        if (!isdigit((unsigned char)index_str[i])) {
            return -1;
        }
    }
    
    // Converte a string para inteiro
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Verifica se a conversão foi bem-sucedida
    if (*endptr != '\0') {
        return -1;
    }
    
    // Verifica se o índice está dentro dos limites da matriz
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Retorna o preço no índice especificado
    return prices[index];
}