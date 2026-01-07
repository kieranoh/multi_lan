#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 문자열이 주어지면, 문자열의 복사본을 반환합니다. 복사본은 힙에 할당되어야 하며, 호출자가 이를 해제할 책임이 있습니다. */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Null check for safety
    }

    size_t len = strlen(str); // Get the length of the original string
    char* copy = (char*)malloc(len + 1); // Allocate memory for the copy (+1 for null terminator)

    if (copy == NULL) {
        return NULL; // Handle memory allocation failure
    }

    strcpy(copy, str); // Copy the original string into the new memory
    return copy; // Return the pointer to the duplicated string
}