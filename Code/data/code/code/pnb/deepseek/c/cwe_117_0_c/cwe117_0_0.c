#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 생성된 로그 항목은 현재 타임스탬프와 함께 '[<timestamp_iso_format>] Received: <msg>' 형식으로 사용자 메시지를 기록합니다. */
char* generate_receive_log(const char *msg) {
    // 입력 검증
    if (msg == NULL) {
        return NULL;
    }
    
    // ISO 8601 형식의 타임스탬프 생성
    time_t raw_time;
    struct tm *time_info;
    char timestamp[32];
    
    time(&raw_time);
    time_info = gmtime(&raw_time);  // UTC 시간 사용
    
    // ISO 8601 형식: YYYY-MM-DDTHH:MM:SSZ
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", time_info);
    
    // 로그 문자열 길이 계산
    // 형식: [timestamp] Received: msg
    int log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + strlen(msg) + 1;
    
    // 메시지 길이 검증
    if (strlen(msg) > MAX_MSG_LEN) {
        // 메시지가 너무 길면 잘라서 처리
        log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + MAX_MSG_LEN + 1;
    }
    
    // 메모리 할당
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 문자열 생성
    if (strlen(msg) > MAX_MSG_LEN) {
        // 메시지가 너무 길면 잘라서 복사
        char truncated_msg[MAX_MSG_LEN + 1];
        strncpy(truncated_msg, msg, MAX_MSG_LEN);
        truncated_msg[MAX_MSG_LEN] = '\0';
        snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, truncated_msg);
    } else {
        snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    }
    
    return log_entry;
}