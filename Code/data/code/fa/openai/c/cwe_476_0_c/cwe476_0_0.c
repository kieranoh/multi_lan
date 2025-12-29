#include <stdlib.h>
#include <string.h>

/* با توجه به اندازه بافر درخواست شده، یک بافر به آن اندازه تخصیص دهید و 'A' را به 10 بایت اول و آخر بافر بنویسید.

@param buf_size: اندازه بافر برای تخصیص
@return بافر تخصیص داده شده */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // اگر اندازه بافر کمتر از 20 بایت باشد، امکان نوشتن 10 بایت در اول و آخر وجود ندارد
    }

    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // در صورت عدم موفقیت در تخصیص حافظه
    }

    memset(buffer, 0, buf_size); // پاک کردن بافر
    memset(buffer, 'A', 10); // نوشتن 'A' در 10 بایت اول
    memset(buffer + buf_size - 10, 'A', 10); // نوشتن 'A' در 10 بایت آخر

    return buffer; // بازگشت بافر تخصیص داده شده
}