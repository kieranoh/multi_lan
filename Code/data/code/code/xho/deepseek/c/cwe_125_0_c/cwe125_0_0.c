#include <stdlib.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Check for NULL pointers
    if (prices == NULL || index_str == NULL) {
        return -1;
    }
    
    // Check for empty string
    if (index_str[0] == '\0') {
        return -1;
    }
    
    // Validate that the string contains only digits (and optional leading minus)
    int i = 0;
    if (index_str[0] == '-') {
        i = 1;
        // If string is just "-", it's invalid
        if (index_str[1] == '\0') {
            return -1;
        }
    }
    
    for (; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return -1;
        }
    }
    
    // Convert string to integer
    int index = atoi(index_str);
    
    // Check if index is within valid bounds
    if (index < 0 || index >= size) {
        return -1;
    }
    
    // Return the price at the valid index
    return prices[index];
}