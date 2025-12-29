#include <stdlib.h>
#include <string.h>

char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* duplicate = (char*)malloc(len * sizeof(char));
    
    if (duplicate != NULL) {
        strcpy(duplicate, str);
    }
    
    return duplicate;
}