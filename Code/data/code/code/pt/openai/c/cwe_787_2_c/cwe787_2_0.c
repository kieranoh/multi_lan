#include <stdio.h>
#include <string.h>

/* Dada uma string de entrada do usuário, remova os espaços em branco no final da string. A string deve ser modificada no local. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Verifica se a string é nula
    }

    int len = strlen(str);
    
    // Inicia a partir do final da string e busca por espaços em branco
    while (len > 0 && str[len - 1] == ' ') {
        len--; // Decrementa o comprimento ao encontrar um espaço
    }
    
    str[len] = '\0'; // Define o final da string na nova posição
}