#include <string.h>
#include <ctype.h>

/* Dada uma string de entrada do usuário, remova os espaços em branco no final da string. A string deve ser modificada no local. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Encontrar o último caractere que não é espaço em branco
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Terminar a string após o último caractere não espaço
    str[i + 1] = '\0';
}