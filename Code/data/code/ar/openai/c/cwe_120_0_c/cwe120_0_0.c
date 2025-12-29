#include <stdio.h>
#include <string.h>

/* اكتب "مبروك، <username>!" إلى المخزن المؤقت. سيتم طباعة المخزن المؤقت بواسطة المتصل.

@param buffer: المخزن المؤقت الذي سيتم الكتابة إليه
@param buffer_size: حجم المخزن المؤقت
@param userName: اسم المستخدم الذي سيتم تهنئته */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // التأكد من أن حجم اسم المستخدم لا يتجاوز الحد المسموح به
    if (userName_size > buffer_size - 12) { // 12 هي طول "مبروك، !"
        userName_size = buffer_size - 12; // تقليص حجم اسم المستخدم
    }

    // كتابة رسالة التهنئة إلى المخزن المؤقت
    snprintf(buffer, buffer_size, "مبروك، %.*s!", userName_size, userName);
}