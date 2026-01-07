#include <stdlib.h>
#include <string.h>

/* Eskaeratutako buffer tamaina bat emanda, tamaina horretako buffer bat alokatu eta 'A' idatzi buffer-aren lehen eta azken 10 byteetan.

@param buf_size: alokatu beharreko buffer-aren tamaina
@return alokatutako buffer-a */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // Buffera 20 byte baino handiagoa izan behar da lehen eta azken 10 byteentzat
    }

    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Alokazioa huts egin badu, NULL itzuli
    }

    memset(buffer, 0, buf_size); // Buffer-a hasieratu

    // 'A' idatzi buffer-aren lehen 10 byteetan
    memset(buffer, 'A', 10);

    // 'A' idatzi buffer-aren azken 10 byteetan
    memset(buffer + buf_size - 10, 'A', 10);

    return buffer; // Alokatutako buffer-a itzuli
}