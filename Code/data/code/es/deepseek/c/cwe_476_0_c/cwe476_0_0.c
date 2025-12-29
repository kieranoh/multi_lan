#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Asignar el búfer del tamaño solicitado
    char* buffer = (char*)malloc(buf_size);
    
    // Verificar si la asignación fue exitosa
    if (buffer == NULL) {
        return NULL;
    }
    
    // Inicializar todo el búfer con ceros (opcional, pero buena práctica)
    memset(buffer, 0, buf_size);
    
    // Escribir 'A' en los primeros 10 bytes si el búfer es lo suficientemente grande
    size_t write_size = 10;
    if (buf_size < write_size) {
        write_size = buf_size;  // Ajustar si el búfer es más pequeño que 10 bytes
    }
    
    if (write_size > 0) {
        memset(buffer, 'A', write_size);
    }
    
    // Escribir 'A' en los últimos 10 bytes si el búfer es lo suficientemente grande
    if (buf_size >= write_size) {
        // Calcular la posición de inicio para los últimos 10 bytes
        size_t start_pos = buf_size - write_size;
        
        // Asegurarse de no sobrescribir los primeros bytes si el búfer es muy pequeño
        if (start_pos >= write_size || start_pos == 0) {
            memset(buffer + start_pos, 'A', write_size);
        }
    }
    
    return buffer;
}