#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // تخصيص المخزن
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // فشل التخصيص
    }
    
    // كتابة 'A' في أول 10 بايت
    size_t write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', write_size);
    
    // كتابة 'A' في آخر 10 بايت إذا كان المخزن كبيرًا بما يكفي
    if (buf_size > 10) {
        size_t last_10_start = buf_size - 10;
        memset(buffer + last_10_start, 'A', 10);
    }
    
    return buffer;
}