#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_price_at_index(int* prices, int size, char* index_str) {
    // Check for NULL pointers
    if (prices == NULL || index_str == NULL) {
        return -1;
    }
    
    // Check for empty string
    if (strlen(index_str) == 0) {
        return -1;
    }
    
    // Validate that the string contains only digits (and optional leading/trailing whitespace)
    char* trimmed_start = index_str;
    // Skip leading whitespace
    while (*trimmed_start && isspace((unsigned char)*trimmed_start)) {
        trimmed_start++;
    }
    
    // If string is only whitespace
    if (*trimmed_start == '\0') {
        return -1;
    }
    
    // Check that all remaining characters are digits
    char* ptr = trimmed_start;
    while (*ptr && !isspace((unsigned char)*ptr)) {
        if (!isdigit((unsigned char)*ptr)) {
            return -1;
        }
        ptr++;
    }
    
    // Convert string to integer
    long index = strtol(trimmed_start, NULL, 10);
    
    // Check for conversion errors or overflow
    if (index < 0 || index >= size) {
        return -1;
    }
    
    return prices[index];
}