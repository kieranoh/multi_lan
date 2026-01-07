#include <stdlib.h>
#include <string.h>

/*
 İstenen bir tampon boyutu verildiğinde, o boyutta bir tampon ayırın ve tamponun ilk ve son 10 baytına 'A' yazın.

 @param buf_size: ayrılacak tamponun boyutu
 @return ayrılan tampon 
*/
char* allocate_buffer_and_write(size_t buf_size) {
    // Tamponu ayır
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        // Bellek ayırma başarısızsa NULL döner
        return NULL;
    }

    // Tamponun ilk 10 baytına 'A' yaz
    memset(buffer, 'A', 10);

    // Eğer tampon boyutu 10 bayttan büyükse, son 10 baytına 'A' yaz
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}