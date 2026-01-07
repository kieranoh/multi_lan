#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Sprawdzenie czy tablica cen istnieje
    if (prices == NULL) {
        return -1;
    }
    
    // Sprawdzenie czy ciąg indeksu istnieje
    if (index_str == NULL) {
        return -1;
    }
    
    // Sprawdzenie czy rozmiar jest nieujemny
    if (size <= 0) {
        return -1;
    }
    
    // Usunięcie białych znaków z początku i końca ciągu
    while (*index_str != '\0' && isspace((unsigned char)*index_str)) {
        index_str++;
    }
    
    char* end_ptr = index_str + strlen(index_str) - 1;
    while (end_ptr > index_str && isspace((unsigned char)*end_ptr)) {
        *end_ptr = '\0';
        end_ptr--;
    }
    
    // Sprawdzenie czy ciąg nie jest pusty po usunięciu białych znaków
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Konwersja ciągu na liczbę całkowitą
    char* conversion_end;
    long index = strtol(index_str, &conversion_end, 10);
    
    // Sprawdzenie czy konwersja się powiodła (cały ciąg został przekonwertowany)
    if (*conversion_end != '\0') {
        return -1;
    }
    
    // Sprawdzenie czy indeks mieści się w zakresie tablicy
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Zwrócenie ceny na podanym indeksie
    return prices[index];
}