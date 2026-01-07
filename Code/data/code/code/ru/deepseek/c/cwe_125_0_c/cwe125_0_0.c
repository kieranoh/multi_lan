#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    if (prices == NULL || index_str == NULL || size <= 0) {
        return -1;
    }
    
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    if (endptr == index_str) {
        return -1;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }
    
    if (index < 0 || index >= size || index > INT_MAX) {
        return -1;
    }
    
    return prices[(int)index];
}