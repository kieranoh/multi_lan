#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // التحقق من المؤشرات الصالحة
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        return;
    }
    
    // إنشاء الرسالة الأساسية
    const char *prefix = "مبروك، ";
    const char *suffix = "!";
    
    // حساب الطول الإجمالي المطلوب
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    int total_len = prefix_len + userName_size + suffix_len;
    
    // التأكد من أن المخزن المؤقت كبير بما يكفي (مع مساحة للصفر النهائي)
    if (total_len >= buffer_size) {
        // إذا كان المخزن المؤقت صغيرًا جدًا، اكتب ما يمكن كتابته بأمان
        int available = buffer_size - 1; // احتفظ بمساحة للصفر النهائي
        
        // نسخ البادئة (بقدر ما يمكن)
        int copy_len = (prefix_len < available) ? prefix_len : available;
        strncpy(buffer, prefix, copy_len);
        available -= copy_len;
        
        // نسخ اسم المستخدم (بقدر ما يمكن)
        if (available > 0) {
            int user_copy_len = (userName_size < available) ? userName_size : available;
            strncpy(buffer + copy_len, userName, user_copy_len);
            available -= user_copy_len;
            copy_len += user_copy_len;
        }
        
        // نسخ اللاحقة (بقدر ما يمكن)
        if (available > 0) {
            int suffix_copy_len = (suffix_len < available) ? suffix_len : available;
            strncpy(buffer + copy_len, suffix, suffix_copy_len);
            copy_len += suffix_copy_len;
        }
        
        // إنهاء السلسلة
        buffer[copy_len] = '\0';
    } else {
        // المخزن المؤقت كبير بما يكفي، انسخ كل شيء
        strcpy(buffer, prefix);
        strncat(buffer, userName, userName_size);
        strcat(buffer, suffix);
    }
}