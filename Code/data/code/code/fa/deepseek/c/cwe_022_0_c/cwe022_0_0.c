#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #define PATH_SEPARATOR '/'
#endif

/**
 * با توجه به مسیر دایرکتوری ارائه شده توسط کاربر و نام فایل، فایل را از دایرکتوری بخوانید و محتوای آن را برگردانید.
 * اگر در طول فرآیند خواندن فایل خطایی رخ دهد (مانند عدم وجود فایل، خطای دسترسی)، یک رشته خالی برگردانید.
 * رشته بازگشتی توسط فراخواننده آزاد خواهد شد.
 *
 * @param filename نام فایلی که باید خوانده شود، که توسط کاربر درخواست شده است.
 * @param dir_path مسیر دایرکتوری که فایل در آن قرار دارد.
 *
 * @return محتوای فایل در صورت وجود و قابل دسترسی بودن، در غیر این صورت یک رشته خالی.
 */
char *read_file_from_dir(const char *filename, const char *dir_path) {
    // بررسی پارامترهای ورودی
    if (filename == NULL || dir_path == NULL || filename[0] == '\0') {
        return strdup("");
    }
    
    // ساخت مسیر کامل فایل
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 برای جداکننده و نال ترمینیتور
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return strdup("");
    }
    
    // ایجاد مسیر کامل با جداکننده مناسب
    snprintf(full_path, total_len, "%s%c%s", dir_path, PATH_SEPARATOR, filename);
    
    // باز کردن فایل
    FILE *file = fopen(full_path, "rb");
    free(full_path);
    
    if (file == NULL) {
        return strdup("");
    }
    
    // رفتن به انتهای فایل برای تعیین اندازه
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return strdup("");
    }
    
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return strdup("");
    }
    
    // بازگشت به ابتدای فایل
    rewind(file);
    
    // تخصیص حافظه برای محتوا (با +1 برای نال ترمینیتور)
    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }
    
    // خواندن محتوای فایل
    size_t bytes_read = fread(content, 1, file_size, file);
    
    // بستن فایل
    fclose(file);
    
    // بررسی موفقیت آمیز بودن خواندن
    if (bytes_read != (size_t)file_size) {
        free(content);
        return strdup("");
    }
    
    // اضافه کردن نال ترمینیتور
    content[file_size] = '\0';
    
    return content;
}