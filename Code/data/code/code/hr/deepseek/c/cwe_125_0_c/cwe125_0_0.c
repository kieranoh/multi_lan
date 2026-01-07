#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Ako je niz cijena NULL ili veličina nije pozitivna, vrati -1
    if (prices == NULL || size <= 0) {
        return -1;
    }
    
    // Ako je string indeksa NULL, vrati -1
    if (index_str == NULL) {
        return -1;
    }
    
    // Preskoči vodeće razmake
    int i = 0;
    while (index_str[i] != '\0' && isspace((unsigned char)index_str[i])) {
        i++;
    }
    
    // Ako je string prazan ili sadrži samo razmake, vrati -1
    if (index_str[i] == '\0') {
        return -1;
    }
    
    // Provjeri je li string valjan broj
    for (int j = i; index_str[j] != '\0'; j++) {
        if (!isdigit((unsigned char)index_str[j]) && !(j == i && index_str[j] == '-')) {
            return -1;
        }
    }
    
    // Pretvori string u broj
    char* endptr;
    long index = strtol(index_str + i, &endptr, 10);
    
    // Provjeri je li konverzija uspjela
    if (endptr == index_str + i) {
        return -1;
    }
    
    // Provjeri je li indeks u rasponu
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Vrati cijenu na zadanom indeksu
    return prices[index];
}