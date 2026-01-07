#include <stdio.h>
#include <stdlib.h>

/**
 * با توجه به اندازه بافر، یک بافر تخصیص دهید و فقط یک خط را از stdin به بافر بخوانید.
 *
 * @param buf_size: اندازه بافر
 * @return بافر حاوی خط خوانده شده از stdin
 */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // چک کردن برای تخصیص موفقیت‌آمیز
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // در صورت خواندن ناموفق، حافظه را آزاد کنید
        return NULL;
    }
    
    return buf;
}