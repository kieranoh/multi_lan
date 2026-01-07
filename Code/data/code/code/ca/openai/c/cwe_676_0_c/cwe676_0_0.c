#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Retorna NULL si no es pot al·locar memòria
    }
    
    // Llegeix una línia de stdin al buffer
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Allibera la memòria si no s'ha pogut llegir
        return NULL;
    }
    
    return buf; // Retorna el buffer amb la línia llegida
}