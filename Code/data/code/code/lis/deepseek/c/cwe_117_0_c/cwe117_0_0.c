#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지입니다.
@return 수신된 메시지에 대한 로그 항목입니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }
    
    time_t now;
    struct tm *timeinfo;
    char timestamp[20];
    
    time(&now);
    timeinfo = localtime(&now);
    
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN - 1) {
        msg_len = MAX_MSG_LEN - 1;
    }
    
    size_t log_len = 2 + strlen(timestamp) + 2 + 10 + 1 + msg_len + 1;
    char *log_entry = (char*)malloc(log_len);
    
    if (log_entry == NULL) {
        return NULL;
    }
    
    snprintf(log_entry, log_len, "[%s] Received: %.*s", timestamp, (int)msg_len, msg);
    
    return log_entry;
}