#include <stdio.h>
#include <stdlib.h>

/* Dado um tamanho de buffer, aloque um buffer e leia apenas uma linha do stdin para o buffer.

@param buf_size: o tamanho do buffer
@return o buffer contendo a linha lida do stdin */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // como estamos lendo apenas uma linha, use uma única linha para ler a linha
    if (buf == NULL) {
        return NULL;  // Falha na alocação
    }
    
    // Lê uma linha do stdin, limitando a leitura ao tamanho do buffer - 1 para deixar espaço para o terminador nulo
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);  // Se a leitura falhar, libera a memória alocada
        return NULL;
    }
    
    // Remove o caractere de nova linha, se presente
    for (int i = 0; i < buf_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    
    return buf;
}