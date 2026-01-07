#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // نظرًا لأننا نقرأ سطرًا واحدًا فقط، استخدم سطرًا واحدًا لقراءة السطر
    if (buf == NULL) {
        return NULL;
    }
    
    // قراءة سطر واحد من stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    return buf;
}