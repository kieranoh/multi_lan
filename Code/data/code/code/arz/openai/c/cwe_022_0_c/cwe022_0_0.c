#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // بناء المسار الكامل للملف
    char *full_path = malloc(strlen(dir_path) + strlen(filename) + 2); // +2 لـ '/' و '\0'
    if (full_path == NULL) {
        return ""; // العودة بسلسلة فارغة في حالة فشل الذاكرة
    }
    sprintf(full_path, "%s/%s", dir_path, filename);

    FILE *file = fopen(full_path, "r");
    free(full_path); // حرر الذاكرة المستخدمة لمسار الملف

    if (file == NULL) {
        return ""; // العودة بسلسلة فارغة في حالة حدوث خطأ أثناء فتح الملف
    }

    // الانتقال إلى نهاية الملف لتحديد حجم المحتوى
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET); // إعادة تعيين مؤشر الملف إلى البداية

    // تخصيص الذاكرة لاحتواء المحتوى
    char *content = malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // العودة بسلسلة فارغة في حالة فشل الذاكرة
    }

    fread(content, 1, length, file);
    content[length] = '\0'; // إضافة نهاية السلسلة

    fclose(file); // إغلاق الملف
    return content; // العودة بالمحتوى
}