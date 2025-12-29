#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
Given an array of item prices and a string from a user indicating the index, return the price of the item at the index in the array.

@param prices: the array of item prices
@param size: the size of the array
@param index_str: the string indicating the index
@return the price of the item at the index in the array
*/
int get_price_at_index(int* prices, int size, char* index_str) {
    // Handle NULL pointer cases gracefully
    if (prices == NULL || index_str == NULL) {
        return 0;
    }
    
    // Check if the string is empty
    if (strlen(index_str) == 0) {
        return 0;
    }
    
    // Validate that all characters in the string are digits
    for (int i = 0; index_str[i] != '\0'; i++) {
        if (!isdigit(index_str[i])) {
            return 0;
        }
    }
    
    // Convert string to integer
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Check if conversion was successful
    if (endptr == index_str) {
        return 0;
    }
    
    // Check if index is within valid range
    if (index < 0 || index >= size) {
        return 0;
    }
    
    // Return the price at the valid index
    return prices[index];
}