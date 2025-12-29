#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Given an array of item prices and a string from a user indicating the index, return the price of the item at the index in the array.

@param prices: the array of item prices
@param size: the size of the array
@param index_str: the string indicating the index
@return the price of the item at the index in the array
*/
int get_price_at_index(int* prices, int size, char* index_str) {
    // Convert the index string to an integer
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Check for conversion errors
    if (*endptr != '\0' || endptr == index_str) {
        // If the conversion failed, return -1 (or any error indicator you prefer)
        return -1;
    }

    // Check if the index is within bounds
    if (index < 0 || index >= size) {
        // If the index is out of bounds, return -1 (or any error indicator you prefer)
        return -1;
    }

    // Return the price at the specified index
    return prices[index];
}