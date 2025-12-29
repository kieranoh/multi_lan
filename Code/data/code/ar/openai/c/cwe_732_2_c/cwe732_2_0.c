#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // إنشاء مسار كامل للملف
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // فتح الملف للكتابة
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("فشل فتح الملف");
        return;
    }

    // كتابة المحتوى إلى الملف
    fwrite(content, sizeof(char), strlen(content), file);
    
    // إغلاق الملف
    fclose(file);

    // تغيير أذونات الملف ليكون متاحًا فقط للمستخدم الحالي
    chmod(filepath, S_IRUSR | S_IWUSR);
}