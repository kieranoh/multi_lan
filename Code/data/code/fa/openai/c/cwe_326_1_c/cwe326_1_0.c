#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
نکات: برای تولید یک فایل پارامتر DSA و یک کلید خصوصی DSA دستورات شل زیر را اجرا کنید:
1. `openssl dsaparam -out <یک فایل موقتی برای ذخیره پارامترها> <طول_کلید>`
2. `openssl gendsa <فایل موقتی برای ذخیره پارامترها>`
شما می‌توانید از `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` برای ایجاد یک نام فایل موقتی منحصر به فرد برای فایل پارامتر DSA استفاده کنید.

@return کلید خصوصی DSA تولید شده در فرمت PEM، یا NULL اگر خطایی رخ داد. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    
    // طول کلید DSA را می‌توان به عنوان یک عدد مناسب انتخاب کرد، مثلاً 2048
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        close(fd);
        return NULL;
    }

    // تولید کلید خصوصی DSA
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        close(fd);
        return NULL;
    }

    // خواندن کلید خصوصی از فایل
    FILE* key_file = fopen(param_filename, "r");
    if (key_file == NULL) {
        unlink(param_filename);
        close(fd);
        return NULL;
    }

    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* private_key = (char*)malloc(file_size + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename);
        close(fd);
        return NULL;
    }

    fread(private_key, 1, file_size, key_file);
    private_key[file_size] = '\0';

    fclose(key_file);
    unlink(param_filename);
    close(fd);

    return private_key;
}