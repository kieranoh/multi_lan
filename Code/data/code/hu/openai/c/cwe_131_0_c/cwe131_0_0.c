#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Adott egy karakterlánc, adja vissza a karakterlánc másolatát. A másolatot a heap-en kell allokálni, és a hívónak kell felszabadítania.

@param str: a másolandó karakterlánc
@return a karakterlánc másolata */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1); // +1 for the null terminator
    if (copy == NULL) {
        return NULL; // allocation failed
    }
    
    strcpy(copy, str);
    return copy;
}