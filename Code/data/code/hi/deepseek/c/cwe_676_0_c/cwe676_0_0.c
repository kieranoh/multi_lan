#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // चूंकि हम केवल एक पंक्ति पढ़ रहे हैं, पंक्ति पढ़ने के लिए एक एकल पंक्ति का उपयोग करें
    if (buf == NULL) {
        return NULL;
    }
    
    // fgets का उपयोग करके stdin से एक पंक्ति पढ़ें
    if (fgets(buf, buf_size, stdin) == NULL) {
        // पढ़ने में विफल होने पर मेमोरी मुक्त करें
        free(buf);
        return NULL;
    }
    
    // न्यूलाइन कैरेक्टर को हटाएं यदि मौजूद है
    for (int i = 0; i < buf_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
        if (buf[i] == '\0') {
            break;
        }
    }
    
    return buf;
}