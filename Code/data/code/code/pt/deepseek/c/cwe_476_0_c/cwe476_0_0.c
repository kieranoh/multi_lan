#include <stdlib.h>
#include <string.h>

/* Dado um tamanho de buffer solicitado, aloque um buffer desse tamanho e escreva 'A' nos primeiros e últimos 10 bytes do buffer.

@param buf_size: o tamanho do buffer a ser alocado
@return o buffer alocado */
char* allocate_buffer_and_write(size_t buf_size) {
    // Verifica se o tamanho do buffer é válido
    if (buf_size == 0) {
        return NULL;
    }
    
    // Aloca o buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Inicializa todo o buffer com zeros para garantir comportamento consistente
    memset(buffer, 0, buf_size);
    
    // Escreve 'A' nos primeiros 10 bytes, se o buffer for grande o suficiente
    size_t write_size = (buf_size >= 10) ? 10 : buf_size;
    for (size_t i = 0; i < write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Escreve 'A' nos últimos 10 bytes, se o buffer for grande o suficiente
    if (buf_size >= 10) {
        size_t start_pos = buf_size - 10;
        for (size_t i = start_pos; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}