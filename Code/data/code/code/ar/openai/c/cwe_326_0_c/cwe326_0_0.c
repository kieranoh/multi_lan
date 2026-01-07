#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const char *key_length = "2048"; // يمكنك تغيير طول المفتاح هنا
    char command[128];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%s 2>/dev/null", key_length);

    FILE *fp;
    char *private_key = NULL;
    size_t key_size = 0;
    
    // فتح عملية تنفيذ الأمر
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // حدث خطأ في فتح العملية
    }

    // قراءة المفتاح الخاص من الخرج
    fseek(fp, 0, SEEK_END);
    key_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    private_key = malloc(key_size + 1); // تخصيص الذاكرة للمفتاح
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // حدث خطأ في تخصيص الذاكرة
    }

    fread(private_key, 1, key_size, fp); // قراءة المفتاح
    private_key[key_size] = '\0'; // إضافة نهاية السلسلة
    pclose(fp); // إغلاق عملية التنفيذ

    return private_key; // إرجاع المفتاح الخاص
}