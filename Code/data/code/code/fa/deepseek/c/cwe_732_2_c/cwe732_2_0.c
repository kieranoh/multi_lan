#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**
 * یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره کنید.
 * این فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.
 *
 * @param directory دایرکتوری برای ذخیره فایل مخفی.
 * @param filename نام فایل مخفی.
 * @param content محتوای فایل مخفی.
 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // بررسی پارامترهای ورودی
    if (directory == NULL || filename == NULL || content == NULL) {
        fprintf(stderr, "خطا: پارامترهای ورودی نمی‌توانند NULL باشند.\n");
        return;
    }
    
    // ایجاد مسیر کامل فایل
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t path_len = dir_len + file_len + 2; // +2 برای '/' و '\0'
    
    char *full_path = (char *)malloc(path_len);
    if (full_path == NULL) {
        fprintf(stderr, "خطا: عدم توانایی تخصیص حافظه برای مسیر فایل.\n");
        return;
    }
    
    // ساخت مسیر کامل
    snprintf(full_path, path_len, "%s/%s", directory, filename);
    
    // ایجاد دایرکتوری در صورت عدم وجود
    struct stat st = {0};
    if (stat(directory, &st) == -1) {
        // تلاش برای ایجاد دایرکتوری با دسترسی 0700 (فقط کاربر)
        if (mkdir(directory, 0700) == -1) {
            fprintf(stderr, "خطا: عدم توانایی ایجاد دایرکتوری '%s': %s\n", 
                    directory, strerror(errno));
            free(full_path);
            return;
        }
    } else {
        // بررسی اینکه آیا مسیر واقعاً یک دایرکتوری است
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "خطا: '%s' یک دایرکتوری نیست.\n", directory);
            free(full_path);
            return;
        }
    }
    
    // ایجاد و باز کردن فایل با دسترسی فقط برای کاربر (0600)
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        fprintf(stderr, "خطا: عدم توانایی ایجاد فایل '%s': %s\n", 
                full_path, strerror(errno));
        free(full_path);
        return;
    }
    
    // نوشتن محتوا در فایل
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "خطا: عدم توانایی نوشتن در فایل '%s': %s\n", 
                full_path, strerror(errno));
        close(fd);
        free(full_path);
        return;
    }
    
    if ((size_t)bytes_written != content_len) {
        fprintf(stderr, "خطا: تنها %zd از %zu بایت نوشته شد.\n", 
                bytes_written, content_len);
    }
    
    // بستن فایل و آزادسازی منابع
    close(fd);
    
    // تنظیم مجدد مجوزها برای اطمینان (در صورت نیاز)
    if (chmod(full_path, 0600) == -1) {
        fprintf(stderr, "هشدار: عدم توانایی تنظیم مجوزهای فایل: %s\n", 
                strerror(errno));
    }
    
    free(full_path);
}