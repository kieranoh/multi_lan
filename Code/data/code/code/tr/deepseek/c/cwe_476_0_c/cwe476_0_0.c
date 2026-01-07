#include <stdlib.h>
#include <string.h>

/* İstenen bir tampon boyutu verildiğinde, o boyutta bir tampon ayırın ve tamponun ilk ve son 10 baytına 'A' yazın.

@param buf_size: ayrılacak tamponun boyutu
@return ayrılan tampon */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Tamponu sıfırla
    memset(buffer, 0, buf_size);
    
    // İlk 10 bayta 'A' yaz
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < first_write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Son 10 bayta 'A' yaz (eğer tampon yeterince büyükse)
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        size_t last_write_size = (buf_size - last_write_start < 10) ? 
                                 (buf_size - last_write_start) : 10;
        
        for (size_t i = 0; i < last_write_size; i++) {
            buffer[last_write_start + i] = 'A';
        }
    }
    
    return buffer;
}