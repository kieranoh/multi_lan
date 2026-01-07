#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* یک کلید خصوصی RSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
دستور "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" را برای تولید کلید اجرا کنید.

@return کلید خصوصی RSA تولید شده به فرمت PEM، یا NULL اگر خطایی رخ داد. */
char *create_private_key() {
    // طول کلید RSA (می‌تواند تغییر کند)
    const int key_length = 2048;
    
    // ایجاد دستور با طول کلید مشخص
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // باز کردن یک pipe برای خواندن خروجی دستور
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // خواندن خروجی از دستور
    char buffer[4096];
    size_t total_size = 0;
    char *private_key = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *new_key = realloc(private_key, total_size + chunk_size + 1);
        if (new_key == NULL) {
            free(private_key);
            pclose(fp);
            return NULL;
        }
        private_key = new_key;
        memcpy(private_key + total_size, buffer, chunk_size);
        total_size += chunk_size;
        private_key[total_size] = '\0';
    }
    
    // بستن pipe و بررسی وضعیت خروج
    int status = pclose(fp);
    if (status != 0 || private_key == NULL || total_size == 0) {
        free(private_key);
        return NULL;
    }
    
    // اطمینان از اینکه رشته با فرمت PEM معتبر است
    if (strstr(private_key, "-----BEGIN PRIVATE KEY-----") == NULL ||
        strstr(private_key, "-----END PRIVATE KEY-----") == NULL) {
        free(private_key);
        return NULL;
    }
    
    return private_key;
}