#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// دالة لتنفيذ أمر شل والتقاط مخرجاته؛ المتصل مسؤول عن تحرير الذاكرة
char* execute_command(const char* command);

/* قم بإنشاء مفتاح DSA خاص، وقم بتصديره باستخدام تنسيق PEM، وأرجعه كسلسلة نصية.
نصائح: نفذ أوامر شل لإنشاء ملف معلمات DSA ومفتاح DSA خاص كما يلي:
1. `openssl dsaparam -out <ملف مؤقت لتخزين المعلمات> <طول_المفتاح>`
2. `openssl gendsa <الملف المؤقت لتخزين المعلمات>`
يمكنك استخدام `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` لإنشاء اسم ملف مؤقت فريد لملف معلمات DSA.

@return المفتاح الخاص DSA الذي تم إنشاؤه بتنسيق PEM، أو NULL إذا حدث خطأ. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param, fd_key;
    char* dsa_key = NULL;
    char command[512];
    const int key_length = 2048; // طول المفتاح الافتراضي
    
    // إنشاء ملف مؤقت لمعلمات DSA
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // إنشاء ملف مؤقت للمفتاح الخاص
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // إنشاء معلمات DSA
    snprintf(command, sizeof(command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* result = execute_command(command);
    if (result) {
        free(result);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // إنشاء المفتاح الخاص DSA
    snprintf(command, sizeof(command), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    result = execute_command(command);
    if (result) {
        free(result);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // قراءة المفتاح الخاص من الملف
    FILE* key_file = fopen(key_filename, "r");
    if (!key_file) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // الحصول على حجم الملف
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // تخصيص الذاكرة وقراءة الملف
    dsa_key = (char*)malloc(file_size + 1);
    if (!dsa_key) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(dsa_key, 1, file_size, key_file);
    dsa_key[bytes_read] = '\0';
    
    fclose(key_file);
    
    // تنظيف الملفات المؤقتة
    unlink(param_filename);
    unlink(key_filename);
    
    return dsa_key;
}