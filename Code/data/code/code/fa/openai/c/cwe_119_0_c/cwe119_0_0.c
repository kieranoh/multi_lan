#include <string.h>

/* از strncpy برای کپی کردن محتویات src به dest تا حد امکان استفاده کنید

@param dest: بافر مقصد
@param dest_size: اندازه بافر مقصد
@param src: بافر منبع
@param src_size: اندازه بافر منبع */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0 || src_size <= 0) {
        return;
    }

    // کپی کردن محتویات با استفاده از strncpy
    strncpy(dest, src, dest_size - 1);

    // اطمینان از اینکه dest به درستی NULL-ترمینیت شده است
    dest[dest_size - 1] = '\0';
}