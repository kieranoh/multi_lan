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
    
    // 현재 시간 가져오기
    time_t now = time(NULL);
    if (now == -1) {
        return NULL;
    }
    
    // ISO 8601 형식으로 시간 변환
    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        return NULL;
    }
    
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS + null terminator
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // 메시지 길이 검증
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN) {
        return NULL;
    }
    
    // 로그 문자열 길이 계산: [timestamp] Received: msg\0
    // timestamp(19) + brackets(2) + space(1) + "Received: "(10) + msg_len + null terminator(1)
    size_t log_len = 19 + 2 + 1 + 10 + msg_len + 1;
    
    // 메모리 할당
    char *log_entry = (char *)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 문자열 생성
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}