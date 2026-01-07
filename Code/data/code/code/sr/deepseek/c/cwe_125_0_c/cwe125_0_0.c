#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Provera da li je niz cena NULL ili veličina negativna
    if (prices == NULL || size <= 0) {
        return -1;
    }
    
    // Provera da li je string indeksa NULL
    if (index_str == NULL) {
        return -1;
    }
    
    // Preskačemo vodeće beline
    int i = 0;
    while (index_str[i] != '\0' && isspace((unsigned char)index_str[i])) {
        i++;
    }
    
    // Provera da li je string prazan nakon uklanjanja belina
    if (index_str[i] == '\0') {
        return -1;
    }
    
    // Provera da li string sadrži samo cifre
    int j = i;
    while (index_str[j] != '\0') {
        if (!isdigit((unsigned char)index_str[j])) {
            return -1;
        }
        j++;
    }
    
    // Konverzija stringa u ceo broj
    char* endptr;
    long index = strtol(index_str + i, &endptr, 10);
    
    // Provera da li je konverzija uspešna
    if (endptr == index_str + i || *endptr != '\0') {
        return -1;
    }
    
    // Provera da li je indeks u opsegu
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Vraćanje cene na datom indeksu
    return prices[index];
}