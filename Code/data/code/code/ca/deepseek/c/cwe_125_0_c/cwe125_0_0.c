#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Donada una matriu de preus d'articles i una cadena d'un usuari que indica l'índex, retorna el preu de l'article a l'índex de la matriu.

@param prices: la matriu de preus d'articles
@param size: la mida de la matriu
@param index_str: la cadena que indica l'índex
@return el preu de l'article a l'índex de la matriu */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Comprovar si la cadena és NULL o buida
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // Comprovar si la matriu de preus és NULL i la mida és vàlida
    if (prices == NULL || size <= 0) {
        return -1;
    }
    
    // Convertir la cadena a un índex enter
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Comprovar si la conversió ha estat exitosa
    if (endptr == index_str) {
        // No s'ha pogut convertir cap caràcter
        return -1;
    }
    
    // Comprovar si hi ha caràcters no vàlids després del número
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            // Hi ha caràcters no vàlids
            return -1;
        }
        endptr++;
    }
    
    // Comprovar si l'índex està dins dels límits
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Retornar el preu a l'índex especificat
    return prices[index];
}