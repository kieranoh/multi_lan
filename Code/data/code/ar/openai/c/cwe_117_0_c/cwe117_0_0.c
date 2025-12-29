#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 256
#define MAX_LOG_LEN (MAX_MSG_LEN + 40) // Buffer for log message

/* قم بإنشاء إدخال سجل لرسالة مستخدم مستلمة مع الطابع الزمني الحالي، بالتنسيق '[<timestamp_iso_format>] تم الاستلام: <msg>'.
@param msg الرسالة المستلمة من المستخدم.
@return إدخال السجل للرسالة المستلمة. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t rawtime;
    struct tm * timeinfo;
    char timestamp[20];
    char *log_entry = (char *)malloc(MAX_LOG_LEN);
    
    if (log_entry == NULL) {
        return NULL; // Memory allocation failed
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);

    snprintf(log_entry, MAX_LOG_LEN, "[%s] تم الاستلام: %s", timestamp, msg);
    
    return log_entry;
}