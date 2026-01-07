#include <string.h>

/* use strncpy para copiar o conteúdo de src para dest o máximo possível

@param dest: o buffer de destino
@param dest_size: o tamanho do buffer de destino
@param src: o buffer de origem
@param src_size: o tamanho do buffer de origem */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Verifica se o tamanho do buffer de destino é maior que 0
    if (dest_size > 0) {
        // Usa strncpy para copiar o conteúdo de src para dest
        strncpy(dest, src, dest_size - 1);
        // Garante que dest seja null-terminado
        dest[dest_size - 1] = '\0';
    }
}