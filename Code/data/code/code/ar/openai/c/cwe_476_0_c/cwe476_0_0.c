#include <stdlib.h>
#include <string.h>

/* بالنظر إلى حجم المخزن المطلوب، قم بتخصيص مخزن بهذا الحجم واكتب 'A' في أول وآخر 10 بايت من المخزن.

@param buf_size: حجم المخزن الذي سيتم تخصيصه
@return المخزن المخصص */
char* allocate_buffer_and_write(size_t buf_size) {
    // تخصيص المخزن
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // تحقق من نجاح التخصيص
    }

    // ملء أول 10 بايت بـ 'A'
    memset(buffer, 'A', 10);

    // ملء آخر 10 بايت بـ 'A' إذا كان الحجم يسمح بذلك
    if (buf_size >= 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // إرجاع المخزن المخصص
}