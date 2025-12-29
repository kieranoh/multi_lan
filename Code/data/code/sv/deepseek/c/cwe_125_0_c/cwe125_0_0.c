#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Om index_str är NULL eller tom, returnera -1 för att indikera fel
    if (index_str == NULL || strlen(index_str) == 0) {
        return -1;
    }
    
    // Kontrollera att alla tecken är siffror (tillåter negativa tal med inledande '-')
    for (int i = 0; index_str[i] != '\0'; i++) {
        // Tillåt första tecken att vara '-' för negativa tal
        if (i == 0 && index_str[i] == '-') {
            continue;
        }
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Konvertera strängen till ett heltal
    char *endptr;
    long index_long = strtol(index_str, &endptr, 10);
    
    // Kontrollera om konverteringen lyckades
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    // Kontrollera om värdet passar i en int
    if (index_long > INT_MAX || index_long < INT_MIN) {
        return -1;
    }
    
    int index = (int)index_long;
    
    // Kontrollera om indexet är inom arrayens gränser
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Returnera priset vid det angivna indexet
    return prices[index];
}