#include <string.h>

/* use strncpy para copiar o conteúdo de src para dest o máximo possível

@param dest: o buffer de destino
@param dest_size: o tamanho do buffer de destino
@param src: o buffer de origem
@param src_size: o tamanho do buffer de origem */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Determinar o número de caracteres a copiar
    int copy_size;
    if (src_size < 0) {
        // Se src_size for negativo, tratamos src como string terminada em nulo
        copy_size = dest_size - 1; // Reserva espaço para o terminador nulo
    } else {
        // Caso contrário, copiamos no máximo src_size caracteres
        copy_size = (src_size < dest_size) ? src_size : (dest_size - 1);
    }
    
    // Copiar os caracteres usando strncpy
    strncpy(dest, src, copy_size);
    
    // Garantir terminação nula
    dest[copy_size] = '\0';
}