#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    time_t raw_time;
    struct tm *time_info;
    char timestamp[21];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    if (time_info == NULL) {
        return NULL;
    }
    
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    int msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    int total_len = 2 + strlen(timestamp) + 2 + 10 + 1 + msg_len + 1;
    char *log_entry = (char*)malloc(total_len * sizeof(char));
    
    if (log_entry == NULL) {
        return NULL;
    }
    
    snprintf(log_entry, total_len, "[%s] Received: %.*s", timestamp, msg_len, msg);
    
    return log_entry;
}