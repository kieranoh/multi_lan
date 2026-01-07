#include <string.h>

/* استخدم strncpy لنسخ محتوى src إلى dest بأقصى قدر ممكن

@param dest: مخزن الوجهة
@param dest_size: حجم مخزن الوجهة
@param src: مخزن المصدر
@param src_size: حجم مخزن المصدر */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // تحجيم الطول الأقصى للنقل
    int copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;

    // نسخ المحتوى من src إلى dest
    strncpy(dest, src, copy_size);

    // التأكد من أن dest ينتهي بـ null
    dest[copy_size] = '\0';
}