#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.

@param msg 수신된 사용자 메시지.
@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    time_t raw_time;
    struct tm *time_info;
    char timestamp[20];
    char *log_entry;
    size_t log_len;
    
    /* 현재 시간 가져오기 */
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    /* ISO 8601 형식으로 타임스탬프 생성 (YYYY-MM-DD HH:MM:SS) */
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", time_info);
    
    /* 로그 항목 길이 계산: 타임스탬프 + 고정 문자열 + 메시지 + 널 종결자 */
    log_len = strlen("[") + strlen(timestamp) + strlen("] Received: ") + strlen(msg) + 1;
    
    /* 메모리 할당 */
    log_entry = (char*)malloc(log_len * sizeof(char));
    if (log_entry == NULL) {
        return NULL;
    }
    
    /* 로그 항목 구성 */
    snprintf(log_entry, log_len, "[%s] Received: %s", timestamp, msg);
    
    return log_entry;
}