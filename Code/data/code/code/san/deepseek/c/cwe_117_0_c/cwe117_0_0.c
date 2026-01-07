#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지.

@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    // 입력 검증
    if (msg == NULL) {
        msg = "(null)";
    }
    
    // ISO 8601 형식의 타임스탬프 생성
    time_t current_time;
    struct tm *time_info;
    char timestamp[32];
    
    time(&current_time);
    time_info = localtime(&current_time);
    
    // ISO 8601 형식: YYYY-MM-DDTHH:MM:SS
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    // 로그 문자열 길이 계산 (타임스탬프 + "[] Received: " + 메시지 + 널 종결자)
    size_t msg_len = strlen(msg);
    size_t log_len = 2 + strlen(timestamp) + 11 + msg_len + 1; // 2: [], 11: " Received: "
    
    // 메시지가 MAX_MSG_LEN을 초과하는 경우 처리
    if (msg_len > MAX_MSG_LEN) {
        msg_len = MAX_MSG_LEN;
        log_len = 2 + strlen(timestamp) + 11 + msg_len + 1;
    }
    
    // 메모리 할당
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 문자열 생성
    if (msg_len > MAX_MSG_LEN) {
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