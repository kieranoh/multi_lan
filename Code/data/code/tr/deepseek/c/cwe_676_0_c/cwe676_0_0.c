#include <stdio.h>
#include <stdlib.h>

/* Bir tampon boyutu verildiğinde, bir tampon ayırın ve stdin'den yalnızca bir satırı tampon içine okuyun.

@param buf_size: tamponun boyutu
@return stdin'den okunan satırı içeren tampon */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // Yalnızca bir satır okuduğumuz için, satırı okumak için tek satırlık bir ifade kullanın
    if (buf != NULL && fgets(buf, buf_size, stdin) != NULL) {
        return buf;
    } else {
        free(buf);
        return NULL;
    }
}