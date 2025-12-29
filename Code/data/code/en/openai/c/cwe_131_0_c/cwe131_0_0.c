#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Given a string, return a duplicate of the string. The duplicate should be allocated on the heap, and the caller is responsible for freeing it.

@param str: the string to duplicate
@return a duplicate of the string
*/
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Handle NULL input gracefully
    }

    // Allocate memory for the duplicate string
    char* duplicate = (char*)malloc(strlen(str) + 1); // +1 for the null terminator
    if (duplicate == NULL) {
        return NULL; // Handle memory allocation failure
    }

    // Copy the original string to the duplicate
    strcpy(duplicate, str);
    return duplicate; // Return the pointer to the duplicated string
}