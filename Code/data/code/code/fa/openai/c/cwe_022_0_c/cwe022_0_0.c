#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // ساختن مسیر کامل فایل
    char *full_path = malloc(strlen(dir_path) + strlen(filename) + 2);
    if (full_path == NULL) {
        return ""; // در صورت عدم موفقیت در تخصیص حافظه، رشته خالی برمی‌گرداند
    }
    sprintf(full_path, "%s/%s", dir_path, filename);

    // باز کردن فایل برای خواندن
    FILE *file = fopen(full_path, "r");
    free(full_path); // آزاد کردن حافظه اختصاص داده شده به full_path
    if (file == NULL) {
        return ""; // در صورت عدم موفقیت در باز کردن فایل، رشته خالی برمی‌گرداند
    }

    // محاسبه اندازه فایل
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // تخصیص حافظه برای محتوای فایل
    char *content = malloc(length + 1);
    if (content == NULL) {
        fclose(file);
        return ""; // در صورت عدم موفقیت در تخصیص حافظه، رشته خالی برمی‌گرداند
    }

    // خواندن محتوای فایل
    fread(content, 1, length, file);
    content[length] = '\0'; // اضافه کردن پایان‌دهنده رشته به محتوای فایل

    fclose(file); // بستن فایل
    return content; // بازگشت محتوای فایل
}