#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL; // خطأ في إنشاء الملف المؤقت
    }
    
    close(fd); // أغلق الوصف الملف بعد إنشائه

    // تنفيذ الأمر لإنشاء معلمات DSA
    char command1[256];
    snprintf(command1, sizeof(command1), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command1) == NULL) {
        unlink(param_filename); // احذف الملف المؤقت عند حدوث خطأ
        return NULL;
    }

    // تنفيذ الأمر لإنشاء المفتاح الخاص DSA
    char command2[256];
    snprintf(command2, sizeof(command2), "openssl gendsa -out /tmp/dsa_private_key.pem %s", param_filename);
    if (execute_command(command2) == NULL) {
        unlink(param_filename); // احذف الملف المؤقت عند حدوث خطأ
        return NULL;
    }

    // قراءة المفتاح الخاص من الملف
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // احذف الملف المؤقت عند حدوث خطأ
        return NULL; // خطأ في فتح ملف المفتاح
    }

    fseek(key_file, 0, SEEK_END);
    long filesize = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char* private_key = (char*)malloc(filesize + 1);
    if (private_key == NULL) {
        fclose(key_file);
        unlink(param_filename); // احذف الملف المؤقت عند حدوث خطأ
        return NULL; // خطأ في تخصيص الذاكرة
    }

    fread(private_key, 1, filesize, key_file);
    private_key[filesize] = '\0'; // تأكد من إنهاء السلسلة بشكل صحيح
    fclose(key_file);

    unlink(param_filename); // احذف الملف المؤقت بعد الانتهاء

    return private_key; // أرجع المفتاح الخاص DSA
}