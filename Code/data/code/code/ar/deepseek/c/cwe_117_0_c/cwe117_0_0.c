#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* قم بإنشاء إدخال سجل لرسالة مستخدم مستلمة مع الطابع الزمني الحالي، بالتنسيق '[<timestamp_iso_format>] تم الاستلام: <msg>'.

@param msg الرسالة المستلمة من المستخدم.

@return إدخال السجل للرسالة المستلمة. */
char* generate_receive_log(const char *msg) {
    // الحصول على الوقت الحالي
    time_t current_time = time(NULL);
    if (current_time == -1) {
        return NULL;
    }
    
    // تحويل الوقت إلى تنسيق ISO 8601 (YYYY-MM-DD HH:MM:SS)
    struct tm *time_info = localtime(&current_time);
    if (time_info == NULL) {
        return NULL;
    }
    
    // تنسيق الطابع الزمني
    char timestamp[20]; // YYYY-MM-DD HH:MM:SS + '\0'
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    // حساب الطول المطلوب للسلسلة الناتجة
    // [timestamp] تم الاستلام: msg\0
    size_t msg_len = strlen(msg);
    size_t total_len = 1 + strlen(timestamp) + 1 + 13 + 2 + msg_len + 1; // 13 لـ " تم الاستلام: "
    
    // التحقق من أن طول الرسالة ضمن الحد المسموح
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }
    
    // تخصيص الذاكرة للسلسلة الناتجة
    char *log_entry = (char *)malloc(total_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // بناء سلسلة السجل
    snprintf(log_entry, total_len, "[%s] تم الاستلام: %s", timestamp, msg);
    
    return log_entry;
}