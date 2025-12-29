#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Vérifier que la taille est suffisante pour écrire dans les 10 premiers et 10 derniers octets
    if (buf_size < 20) {
        // Si la taille est insuffisante, allouer un tampon mais ne pas écrire au-delà des limites
        char* buffer = (char*)malloc(buf_size);
        if (buffer == NULL) {
            return NULL;
        }
        
        // Écrire 'A' dans les premiers octets disponibles
        size_t bytes_to_write = buf_size;
        if (bytes_to_write > 10) {
            bytes_to_write = 10;
        }
        memset(buffer, 'A', bytes_to_write);
        
        // Écrire 'A' dans les derniers octets disponibles
        if (buf_size > 10) {
            size_t last_bytes_start = buf_size - 10;
            if (last_bytes_start < 10) {
                last_bytes_start = 10; // Éviter le chevauchement
            }
            size_t last_bytes_count = buf_size - last_bytes_start;
            if (last_bytes_count > 0) {
                memset(buffer + last_bytes_start, 'A', last_bytes_count);
            }
        }
        
        return buffer;
    }
    
    // Allouer le tampon
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Écrire 'A' dans les 10 premiers octets
    memset(buffer, 'A', 10);
    
    // Écrire 'A' dans les 10 derniers octets
    memset(buffer + buf_size - 10, 'A', 10);
    
    return buffer;
}