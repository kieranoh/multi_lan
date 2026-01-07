#include <string.h>

/**
 * از strncpy برای کپی کردن محتویات src به dest تا حد امکان استفاده کنید
 * 
 * @param dest: بافر مقصد
 * @param dest_size: اندازه بافر مقصد
 * @param src: بافر منبع
 * @param src_size: اندازه بافر منبع
 */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* اطمینان از اینکه حداقل یک بایت برای کاراکتر پایان‌دهنده رشته باقی می‌ماند */
    int max_copy_size = dest_size - 1;
    
    /* تعیین تعداد کاراکترهایی که باید کپی شوند */
    int copy_size = src_size;
    if (copy_size > max_copy_size) {
        copy_size = max_copy_size;
    }
    
    /* کپی کردن محتوا با استفاده از strncpy */
    strncpy(dest, src, copy_size);
    
    /* اطمینان از پایان‌دهی رشته */
    dest[copy_size] = '\0';
}