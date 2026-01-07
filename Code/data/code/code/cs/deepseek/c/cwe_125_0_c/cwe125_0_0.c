#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Pokud je řetězec indexu NULL nebo prázdný, vrátíme -1 (chyba)
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // Zkontrolujeme, zda řetězec obsahuje pouze číslice
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Převedeme řetězec na celé číslo
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Zkontrolujeme, zda konverze proběhla úspěšně
    if (*endptr != '\0') {
        return -1;
    }
    
    // Zkontrolujeme, zda je index v platném rozsahu
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Vrátíme cenu na daném indexu
    return prices[index];
}