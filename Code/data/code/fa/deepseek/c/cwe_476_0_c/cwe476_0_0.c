#include <stdlib.h>
#include <string.h>

/**
 * با توجه به اندازه بافر درخواست شده، یک بافر به آن اندازه تخصیص دهید و 'A' را به 10 بایت اول و آخر بافر بنویسید.
 * 
 * @param buf_size: اندازه بافر برای تخصیص
 * @return بافر تخصیص داده شده یا NULL در صورت شکست
 */
char* allocate_buffer_and_write(size_t buf_size) {
    // بررسی اندازه معتبر
    if (buf_size == 0) {
        return NULL;
    }
    
    // تخصیص بافر
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // مقداردهی اولیه بافر با صفر (اختیاری)
    memset(buffer, 0, buf_size);
    
    // نوشتن 'A' به 10 بایت اول
    size_t write_size_first = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', write_size_first);
    
    // نوشتن 'A' به 10 بایت آخر
    if (buf_size >= 10) {
        size_t write_size_last = (buf_size < 20) ? (buf_size - 10) : 10;
        memset(buffer + buf_size - write_size_last, 'A', write_size_last);
    }
    
    return buffer;
}