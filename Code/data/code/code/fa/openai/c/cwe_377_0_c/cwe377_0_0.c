#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    // ایجاد یک نام فایل موقت
    char* temp_filename = tmpnam(NULL);
    if (temp_filename == NULL) {
        return NULL;  // در صورت بروز خطا در ایجاد نام فایل
    }

    // ایجاد و باز کردن فایل برای نوشتن
    FILE* file = fopen(temp_filename, "w");
    if (file == NULL) {
        return NULL;  // در صورت بروز خطا در باز کردن فایل
    }

    // نوشتن محتوای results در فایل
    fputs(results, file);

    // بستن فایل
    fclose(file);

    // بازگشت نام فایل موقت
    return strdup(temp_filename);  // تخصیص دینامیک نام فایل
}