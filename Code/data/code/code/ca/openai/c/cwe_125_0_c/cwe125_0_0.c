#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Donada una matriu de preus d'articles i una cadena d'un usuari que indica l'índex, retorna el preu de l'article a l'índex de la matriu.
   
@param prices: la matriu de preus d'articles
@param size: la mida de la matriu
@param index_str: la cadena que indica l'índex
@return el preu de l'article a l'índex de la matriu */
int get_price_at_index(int* prices, int size, char* index_str) {
    int index = atoi(index_str); // Convertir la cadena a enter

    // Comprovar si l'índex està dins dels límits de la matriu
    if (index < 0 || index >= size) {
        return -1; // Retorna -1 si l'índex és invàlid
    }

    return prices[index]; // Retorna el preu de l'article a l'índex especificat
}