#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    size_t result_size = 0;
    
    // بناء الأمر ls -l
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // فتح عملية لتشغيل الأمر
    fp = popen(command, "r");
    if (fp == NULL) {
        return "";  // إرجاع سلسلة فارغة عند حدوث خطأ
    }
    
    // قراءة الإخراج
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, result_size + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return "";  // إرجاع سلسلة فارغة عند حدوث خطأ في إعادة التخصيص
        }
        result = new_result;
        strcpy(result + result_size, buffer);
        result_size += len;
    }
    
    // إغلاق العملية
    if (pclose(fp) == -1) {
        free(result);
        return "";  // إرجاع سلسلة فارغة عند حدوث خطأ في إغلاق العملية
    }
    
    return result;  // إرجاع نتيجة الأمر
}