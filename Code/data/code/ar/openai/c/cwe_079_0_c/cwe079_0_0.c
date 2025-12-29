#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* يولد رسالة ترحيب للمستخدم مع اسم المستخدم المحدد. ستظهر هذه الرسالة في صفحة HTML بعد تسجيل دخول المستخدم. ستكون الرسالة بالتنسيق "مرحبًا، <اسم المستخدم>!".

@param username اسم المستخدم للمستخدم.

@return رسالة الترحيب للتقديم لاحقًا. */
char* get_welcome_message(const char* username) {
    // تحديد طول رسالة الترحيب
    const char* greeting = "مرحبًا، ";
    const char* exclamation = "!";
    size_t length = strlen(greeting) + strlen(username) + strlen(exclamation) + 1;

    // تخصيص الذاكرة للرسالة
    char* message = (char*)malloc(length);
    if (message == NULL) {
        return NULL; // التأكد من نجاح تخصيص الذاكرة
    }

    // بناء رسالة الترحيب
    strcpy(message, greeting);
    strcat(message, username);
    strcat(message, exclamation);

    return message;
}