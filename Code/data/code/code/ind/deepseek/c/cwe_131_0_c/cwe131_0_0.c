#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len * sizeof(char));
    
    if (copy == NULL) {
        return NULL;
    }
    
    memcpy(copy, str, len);
    return copy;
}