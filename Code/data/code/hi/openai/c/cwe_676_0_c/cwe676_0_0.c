#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // मेमोरी आवंटन विफल
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // पढ़ने में विफलता पर मेमोरी मुक्त करें
        return NULL;
    }
    
    return buf; // सफलतापूर्वक पढ़ा गया बफर लौटाएं
}