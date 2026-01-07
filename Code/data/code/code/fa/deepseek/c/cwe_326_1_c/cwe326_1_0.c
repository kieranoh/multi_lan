#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// اعلام تابع execute_command
char* execute_command(const char* command);

char* create_dsa_key() {
    // طول کلید DSA (می‌توانید این مقدار را تغییر دهید)
    const char* key_length = "2048";
    
    // ایجاد یک فایل موقتی برای پارامترهای DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL;
    }
    
    // بستن فایل توصیف‌گر زیرا mkstemp فقط فایل را ایجاد می‌کند
    close(fd);
    
    // ساخت دستور برای تولید پارامترهای DSA
    char param_command[512];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %s", param_filename, key_length);
    
    // اجرای دستور برای تولید پارامترها
    char* param_result = execute_command(param_command);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);
    
    // ساخت دستور برای تولید کلید خصوصی DSA
    char key_command[512];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s", param_filename);
    
    // اجرای دستور برای تولید کلید خصوصی
    char* key_result = execute_command(key_command);
    
    // حذف فایل موقتی پارامترها
    remove(param_filename);
    
    // بررسی نتیجه
    if (key_result == NULL || strlen(key_result) == 0) {
        if (key_result != NULL) {
            free(key_result);
        }
        return NULL;
    }
    
    return key_result;
}