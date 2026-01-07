#include <stdlib.h>
#include <string.h>

/* Dada uma string, retorne uma duplicata da string. A duplicata deve ser alocada na heap, e o chamador é responsável por liberá-la.

@param str: a string a ser duplicada
@return uma duplicata da string */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL; // Retorna NULL se a string de entrada for NULL
    }
    
    size_t len = strlen(str); // Calcula o comprimento da string
    char* dup = (char*)malloc(len + 1); // Aloca memória para a duplicata + 1 para o caractere nulo

    if (dup == NULL) {
        return NULL; // Retorna NULL se a alocação falhar
    }

    strcpy(dup, str); // Copia a string original para a nova alocação
    return dup; // Retorna a nova duplicata
}