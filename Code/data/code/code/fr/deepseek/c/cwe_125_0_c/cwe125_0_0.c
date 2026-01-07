#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Vérification des paramètres d'entrée
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // Vérifier si la chaîne est vide
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Vérifier si la chaîne contient uniquement des chiffres
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)index_str[i])) {
            return -1;
        }
    }
    
    // Convertir la chaîne en entier
    char *endptr;
    long index_long = strtol(index_str, &endptr, 10);
    
    // Vérifier la conversion
    if (*endptr != '\0') {
        return -1;
    }
    
    // Vérifier les dépassements
    if (index_long < INT_MIN || index_long > INT_MAX) {
        return -1;
    }
    
    int index = (int)index_long;
    
    // Vérifier si l'index est dans les limites du tableau
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Retourner le prix à l'index
    return prices[index];
}