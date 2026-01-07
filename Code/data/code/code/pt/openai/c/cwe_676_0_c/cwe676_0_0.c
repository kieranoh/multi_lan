#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Retorna NULL se a alocação falhar
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Libera o buffer se a leitura falhar
        return NULL;
    }
    
    return buf; // Retorna o buffer contendo a linha lida
}