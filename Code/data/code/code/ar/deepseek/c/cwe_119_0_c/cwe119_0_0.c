#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // احسب الحد الأدنى للحجم الذي يمكن نسخه
    int copy_size = (src_size < dest_size) ? src_size : dest_size - 1;
    
    // استخدم strncpy لنسخ البيانات
    strncpy(dest, src, copy_size);
    
    // تأكد من إنهاء السلسلة بشكل صحيح
    dest[copy_size] = '\0';
}