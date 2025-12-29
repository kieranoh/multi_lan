#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Tarkistetaan, että taulukko ja merkkijono ovat kelvollisia
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    // Poistetaan mahdolliset välilyönnit merkkijonon alusta ja lopusta
    while (isspace((unsigned char)*index_str)) {
        index_str++;
    }
    
    // Tarkistetaan, että merkkijono ei ole tyhjä
    if (*index_str == '\0') {
        return -1;
    }
    
    // Muunnetaan merkkijono kokonaisluvuksi
    char *endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Tarkistetaan, että koko merkkijono muunnettiin onnistuneesti
    // ja että se ei sisällä ylimääräisiä merkkejä (paitsi välilyöntejä lopussa)
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
        return -1;
    }
    
    // Tarkistetaan, että indeksi on kelvollinen taulukon sisällä
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Palautetaan hinta annetusta indeksistä
    return prices[index];
}