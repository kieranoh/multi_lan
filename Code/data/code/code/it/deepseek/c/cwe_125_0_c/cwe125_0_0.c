#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Controllo dei parametri di input
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // Controlla se la stringa è vuota
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Verifica che tutti i caratteri siano cifre (per interi non negativi)
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Converte la stringa in intero
    char* endptr;
    long index_long = strtol(index_str, &endptr, 10);
    
    // Controlla errori di conversione
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // Controlla overflow e che l'indice sia valido
    if (index_long < 0 || index_long >= size || index_long > INT_MAX) {
        return -1;
    }
    
    int index = (int)index_long;
    
    // Restituisce il prezzo all'indice specificato
    return prices[index];
}