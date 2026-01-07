#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 생성된 로그 항목은 현재 타임스탬프와 함께 '[<timestamp_iso_format>] Received: <msg>' 형식으로 사용자 메시지를 기록합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t now;
    struct tm *timeinfo;
    char timestamp[32];
    
    time(&now);
    timeinfo = localtime(&now);
    
    if (timeinfo == NULL) {
        return NULL;
    }
    
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", timeinfo);
    
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    size_t log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + msg_len + 1;
    char *log_entry = (char*)malloc(log_len);
    
    if (log_entry == NULL) {
        return NULL;
    }
    
    snprintf(log_entry, log_len, "[%s] Received: %.*s", timestamp, (int)msg_len, msg);
    
    return log_entry;
}