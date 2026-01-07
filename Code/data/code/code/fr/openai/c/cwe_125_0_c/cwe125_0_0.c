#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Étant donné un tableau de prix d'articles et une chaîne d'un utilisateur indiquant l'index, renvoyez le prix de l'article à l'index dans le tableau.

@param prices: le tableau des prix des articles
@param size: la taille du tableau
@param index_str: la chaîne indiquant l'index
@return le prix de l'article à l'index dans le tableau */
int get_price_at_index(int* prices, int size, char* index_str) {
    // Convertir la chaîne index_str en entier
    int index = atoi(index_str);
    
    // Vérifier si l'index est valide
    if (index < 0 || index >= size) {
        return -1; // Retourne -1 pour indiquer un index invalide
    }
    
    // Retourner le prix à l'index donné
    return prices[index];
}