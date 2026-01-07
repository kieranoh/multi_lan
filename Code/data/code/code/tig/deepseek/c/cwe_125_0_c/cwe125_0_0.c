#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    if (endptr == index_str || *endptr != '\0') {
        return -1;
    }
    
    if (index < 0 || index >= size) {
        return -1;
    }
    
    return prices[index];
}