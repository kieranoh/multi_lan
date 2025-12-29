#include <stdlib.h>
#include <string.h>

/* Dado um tamanho de buffer solicitado, aloque um buffer desse tamanho e escreva 'A' nos primeiros e últimos 10 bytes do buffer.

@param buf_size: o tamanho do buffer a ser alocado
@return o buffer alocado */
char* allocate_buffer_and_write(size_t buf_size) {
    // Aloca o buffer com o tamanho solicitado
    char* buffer = (char*)malloc(buf_size);
    
    // Verifica se a alocação foi bem-sucedida
    if (buffer == NULL) {
        return NULL; // Retorna NULL em caso de falha na alocação
    }

    // Inicializa o buffer com zeros
    memset(buffer, 0, buf_size);

    // Escreve 'A' nos primeiros 10 bytes, respeitando o limite do buffer
    size_t first_limit = buf_size < 10 ? buf_size : 10;
    memset(buffer, 'A', first_limit);

    // Escreve 'A' nos últimos 10 bytes, respeitando o limite do buffer
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}