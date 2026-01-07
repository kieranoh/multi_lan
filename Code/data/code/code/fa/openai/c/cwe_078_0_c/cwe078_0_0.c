#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // اندازه‌گیری طول خروجی
    size_t buffer_size = 1024;
    char *output = (char *)malloc(buffer_size);
    if (!output) {
        return ""; // اگر تخصیص حافظه ناموفق باشد، رشته خالی برگردانید
    }

    // ساخت دستور `ls -l` با استفاده از مسیر دایرکتوری
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // اجرای دستور و خواندن خروجی
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output);
        return ""; // اگر خطایی در اجرای دستور وجود داشته باشد، رشته خالی برگردانید
    }

    // خواندن خروجی به buffer
    size_t total_read = 0;
    while (fgets(output + total_read, buffer_size - total_read, fp) != NULL) {
        total_read += strlen(output + total_read);
        if (total_read >= buffer_size - 1) {
            buffer_size *= 2; // دو برابر کردن اندازه buffer
            output = (char *)realloc(output, buffer_size);
            if (!output) {
                pclose(fp);
                return ""; // اگر realloc ناموفق باشد، رشته خالی برگردانید
            }
        }
    }

    // بستن جریان و بررسی خطا
    if (pclose(fp) == -1) {
        free(output);
        return ""; // اگر در بستن جریان خطایی وجود داشته باشد، رشته خالی برگردانید
    }

    return output; // خروجی را برگرداند
}