#include <stdio.h>
#include <stdlib.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Convert the index from string to integer
    int index = atoi(index_str);
    
    // Check if the index is within bounds
    if (index < 0 || index >= size) {
        // Return -1 or any other value to indicate an error
        return -1; // Error: index out of bounds
    }
    
    // Return the price at the specified index
    return prices[index];
}