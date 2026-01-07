#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // طول المفتاح
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // تنفيذ الأمر
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // فشل في تنفيذ الأمر
    }

    // قراءة المفتاح من الخرج
    char *private_key = malloc(4096); // تخصيص الذاكرة للمفتاح
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // فشل في تخصيص الذاكرة
    }

    size_t read_bytes = fread(private_key, 1, 4096, fp);
    private_key[read_bytes] = '\0'; // إضافة نهاية السلسلة

    // إغلاق العملية
    pclose(fp);

    // تحقق مما إذا تم قراءة أي بيانات
    if (read_bytes == 0) {
        free(private_key);
        return NULL; // لم يتم قراءة أي بيانات
    }

    return private_key; // إرجاع المفتاح الخاص
}