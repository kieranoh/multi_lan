#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Dada una matriz de precios de artículos y una cadena de un usuario que indica el índice, devuelve el precio del artículo en el índice de la matriz.

@param prices: la matriz de precios de artículos
@param size: el tamaño de la matriz
@param index_str: la cadena que indica el índice
@return el precio del artículo en el índice de la matriz */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // Convertir la cadena a un entero

    // Verificar si el índice está dentro de los límites de la matriz
    if (index < 0 || index >= size) {
        return -1; // Retornar -1 si el índice es inválido
    }

    return prices[index]; // Retornar el precio en el índice dado
}