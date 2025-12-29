#include <stdlib.h>
#include <string.h>

/* Dada uma string, retorne uma duplicata da string. A duplicata deve ser alocada na heap, e o chamador é responsável por liberá-la.

@param str: a string a ser duplicada
@return uma duplicata da string */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* duplicate = (char*)malloc(len * sizeof(char));
    
    if (duplicate == NULL) {
        return NULL;
    }
    
    strcpy(duplicate, str);
    return duplicate;
}