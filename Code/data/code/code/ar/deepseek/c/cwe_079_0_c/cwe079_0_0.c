#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // البادئة الأساسية للرسالة
    const char* prefix = "مرحبًا، ";
    const char* suffix = "!";
    
    // حساب الطول الإجمالي للرسالة
    // الطول = طول البادئة + طول اسم المستخدم + طول اللاحقة + 1 للحرف الختامي
    size_t total_length = strlen(prefix) + strlen(username) + strlen(suffix) + 1;
    
    // تخصيص الذاكرة للرسالة
    char* message = (char*)malloc(total_length * sizeof(char));
    
    // التحقق من نجاح تخصيص الذاكرة
    if (message == NULL) {
        return NULL;
    }
    
    // بناء الرسالة
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}