#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    // 입력 검증
    if (msg == NULL) {
        return NULL;
    }
    
    // ISO 8601 형식의 타임스탬프 생성
    time_t current_time;
    struct tm *time_info;
    char timestamp[32];
    
    time(&current_time);
    time_info = localtime(&current_time);
    
    // ISO 8601 형식: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // 메시지 길이 검증
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
    }
    
    // 로그 문자열 메모리 할당
    // 형식: [timestamp] Received: msg
    // 필요한 공간: '[' + timestamp + '] Received: ' + msg + '\0'
    size_t log_len = 1 + strlen(timestamp) + 1 + 11 + 2 + msg_len + 1;
    char *log_entry = (char*)malloc(log_len);
    
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 문자열 구성
    snprintf(log_entry, log_len, "[%s] Received: %.*s", 
             timestamp, (int)msg_len, msg);
    
    return log_entry;
}