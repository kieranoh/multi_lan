int get_price_at_index(int* prices, int size, char* index_str) {
    // Convert string to integer
    char* endptr;
    long index = strtol(index_str, &endptr, 10);
    
    // Check if conversion was successful
    if (*endptr != '\0') {
        return -1; // Invalid index string
    }
    
    // Check if index is within bounds
    if (index < 0 || index >= size) {
        return -1; // Index out of bounds
    }
    
    // Return the price at the valid index
    return prices[index];
}