#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Bellek ayırma başarısız olduysa NULL döndür
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Satır okunamadıysa belleği serbest bırak
        return NULL;
    }
    
    return buf; // Başarıyla okunan satırı döndür
}