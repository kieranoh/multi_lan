#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Controleer of de array pointer geldig is
    if (prices == NULL) {
        return -1;
    }
    
    // Controleer of de index string geldig is
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // Controleer of de string alleen cijfers bevat
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Converteer de string naar een integer
    int index = atoi(index_str);
    
    // Controleer of de index binnen de grenzen van de array valt
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Retourneer de prijs op de gevraagde index
    return prices[index];
}