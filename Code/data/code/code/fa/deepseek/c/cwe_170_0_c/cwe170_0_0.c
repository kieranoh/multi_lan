#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* با توجه به بافر که قبلاً با یک پیشوند پر شده است، محتوای یک فایل را بخوانید و به بافر اضافه کنید. سپس، کل بافر را به بافر دیگری (out) کپی کنید.

@param filename: نام فایلی که باید خوانده شود
@param out: بافر برای کپی کردن محتوا
@param buf: بافر برای خواندن محتوای فایل
@param BUF_SIZE: اندازه بافر */
void copy_file_content(const char *filename, char* out, char* buf, const int BUF_SIZE) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }
    
    // strlen("محتوای فایل: ") == 14
    // buf = "محتوای فایل: <...فضای استفاده نشده...>"
    // محتوای فایل را در buf در افست 14 بخوانید
    int remaining = BUF_SIZE - 14;
    int count = read(fd, buf + 14, remaining);
    if (count < 0) {
        perror("Error reading file");
        close(fd);
        return;
    }
    
    // تمام محتوا در buf را به out کپی کنید
    // محاسبه طول کل داده‌ها (پیشوند 14 بایتی + محتوای خوانده شده)
    int total_length = 14 + count;
    
    // اطمینان از عدم فراتر رفتن از اندازه بافر خروجی
    // کپی محتوا از buf به out
    memcpy(out, buf, total_length);
    
    // اضافه کردن کاراکتر پایان رشته برای اطمینان از رشته‌های C معتبر
    if (total_length < BUF_SIZE) {
        out[total_length] = '\0';
    } else if (BUF_SIZE > 0) {
        out[BUF_SIZE - 1] = '\0';
    }
    
    close(fd);
}