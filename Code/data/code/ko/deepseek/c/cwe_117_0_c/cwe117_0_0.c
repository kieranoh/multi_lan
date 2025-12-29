#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프를 사용하여 '[<timestamp_iso_format>] 수신됨: <msg>' 형식의 사용자 메시지 로그 항목을 생성합니다.

@param msg 수신된 사용자 메시지입니다.
@return 수신된 메시지에 대한 로그 항목입니다. */
char* generate_receive_log(const char *msg) {
    time_t raw_time;
    struct tm *time_info;
    char timestamp[32];
    char *log_entry;
    size_t log_len;
    
    /* 현재 시간 가져오기 */
    time(&raw_time);
    time_info = localtime(&raw_time);
    
    /* ISO 8601 형식으로 타임스탬프 생성 (YYYY-MM-DDTHH:MM:SS) */
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", time_info);
    
    /* 로그 항목의 총 길이 계산 */
    log_len = strlen("[") + strlen(timestamp) + strlen("] 수신됨: ") + 
              strlen(msg) + 1; /* 널 종결자를 위한 +1 */
    
    /* 메시지가 너무 길면 잘라내기 */
    if (strlen(msg) > MAX_MSG_LEN - 1) {
        log_len = strlen("[") + strlen(timestamp) + strlen("] 수신됨: ") + 
                  MAX_MSG_LEN;
    }
    
    /* 메모리 할당 */
    log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    /* 로그 항목 구성 */
    if (strlen(msg) > MAX_MSG_LEN - 1) {
        char truncated_msg[MAX_MSG_LEN];
        strncpy(truncated_msg, msg, MAX_MSG_LEN - 1);
        truncated_msg[MAX_MSG_LEN - 1] = '\0';
        snprintf(log_entry, log_len, "[%s] 수신됨: %s", timestamp, truncated_msg);
    } else {
        snprintf(log_entry, log_len, "[%s] 수신됨: %s", timestamp, msg);
    }
    
    return log_entry;
}