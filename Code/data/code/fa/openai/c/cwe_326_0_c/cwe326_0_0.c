#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // طول کلید RSA
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // اجرای دستور و باز کردن لوله برای خواندن خروجی
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // در صورت بروز خطا در باز کردن لوله
    }

    // خواندن خروجی دستور
    char *private_key = NULL;
    size_t len = 0;
    ssize_t read;

    // تخصیص حافظه برای کلید خصوصی
    private_key = (char *)malloc(4096); // فرض می‌کنیم کلید حداکثر 4096 بایت است
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // در صورت بروز خطا در تخصیص حافظه
    }
    
    // خواندن داده‌ها از لوله
    while ((read = fread(private_key + len, 1, 4096 - len, fp)) > 0) {
        len += read;
        if (len >= 4096) {
            break; // از حداکثر اندازه عبور نکنید
        }
    }
    
    private_key[len] = '\0'; // اطمینان از اینکه رشته Null-terminated است

    // بستن لوله
    pclose(fp);

    // اگر هیچ داده‌ای خوانده نشد، آزاد کردن حافظه و بازگشت NULL
    if (len == 0) {
        free(private_key);
        return NULL;
    }

    return private_key; // بازگشت کلید خصوصی
}