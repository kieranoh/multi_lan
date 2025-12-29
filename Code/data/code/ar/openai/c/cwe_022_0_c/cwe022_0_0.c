#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // إعداد مسار الملف الكامل
    char *full_path = malloc(strlen(dir_path) + strlen(filename) + 2); // 1 لـ '/' و 1 لـ '\0'
    if (full_path == NULL) {
        return ""; // في حال فشل التخصيص
    }

    sprintf(full_path, "%s/%s", dir_path, filename); // بناء مسار الملف الكامل

    // فتح الملف
    FILE *file = fopen(full_path, "r");
    free(full_path); // تحرير ذاكرة مسار الملف

    if (file == NULL) {
        return ""; // في حالة عدم العثور على الملف أو حدوث خطأ في الإذن
    }

    // الانتقال إلى نهاية الملف لقياس الطول
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET); // إعادة تعيين مؤشر الملف إلى البداية

    // تخصيص الذاكرة لمحتوى الملف
    char *content = malloc(file_size + 1); // +1 لـ '\0'
    if (content == NULL) {
        fclose(file);
        return ""; // في حال فشل التخصيص
    }

    // قراءة محتوى الملف
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // إضافة نهاية السلسلة

    fclose(file); // إغلاق الملف
    return content; // إرجاع محتوى الملف
}