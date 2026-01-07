#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* write_results(const char* results) {
    /* یک فایل موقت ایجاد کنید، نتایج ارائه شده را در آن بنویسید و نام فایل را برای خواندن بیشتر برگردانید.
    
    @param results محتوای رشته‌ای که باید در فایل موقت نوشته شود
    @return یک رشته به‌طور دینامیک تخصیص‌یافته که نام فایل موقت را شامل می‌شود. */
    
    if (results == NULL) {
        return NULL;
    }
    
    // ایجاد الگوی نام فایل موقت
    char template[] = "/tmp/results_XXXXXX";
    
    // ایجاد فایل موقت با استفاده از mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // نوشتن نتایج در فایل
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template); // حذف فایل در صورت خطا
        return NULL;
    }
    
    // بستن فایل
    close(fd);
    
    // تخصیص حافظه برای نام فایل و کپی کردن آن
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template); // حذف فایل در صورت خطا
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}