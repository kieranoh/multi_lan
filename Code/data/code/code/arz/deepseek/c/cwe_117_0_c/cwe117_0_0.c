#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지.

@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    // ISO 8601 형식의 타임스탬프를 위한 버퍼 (예: "2024-01-15T14:30:45")
    char timestamp[20];
    time_t current_time;
    struct tm *time_info;
    
    // 현재 시간 가져오기
    time(&current_time);
    time_info = localtime(&current_time);
    
    // ISO 8601 형식으로 타임스탬프 생성
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // 로그 문자열 길이 계산
    // 형식: "[YYYY-MM-DDTHH:MM:SS] Received: <msg>\0"
    int log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + strlen(msg) + 1;
    
    // 메모리 할당
    char *log_entry = (char*)malloc(log_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }
    
    // 로그 문자열 생성
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}