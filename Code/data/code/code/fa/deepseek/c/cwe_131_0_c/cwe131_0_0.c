#include <stdlib.h>
#include <string.h>

/**
 * یک رشته را دریافت کرده و یک نسخه از آن را برمی‌گرداند.
 * نسخه باید در حافظه دینامیک تخصیص داده شود و مسئولیت آزادسازی آن بر عهده فراخوانی‌کننده است.
 *
 * @param str: رشته‌ای که باید نسخه‌برداری شود
 * @return نسخه‌ای از رشته در صورت موفقیت، NULL در صورت خطا
 */
char* my_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len * sizeof(char));
    
    if (copy == NULL) {
        return NULL;
    }
    
    memcpy(copy, str, len);
    return copy;
}