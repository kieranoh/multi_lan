#define MAX_MSG_LEN 256

#include <time.h>
#include <string.h>
#include <stdlib.h>

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    // ISO 8601 형식의 타임스탬프 생성
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 8601 형식: YYYY-MM-DDTHH:MM:SS
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);
    
    // 메시지 길이 확인 (MAX_MSG_LEN을 초과하지 않도록)
    size_t msg_len = strlen(msg);
    if (msg_len > MAX_MSG_LEN - 1) {
        msg_len = MAX_MSG_LEN - 1;
    }
    
    // 로그 문자열 길이 계산: '[YYYY-MM-DDTHH:MM:SS] Received: ' + msg + '\0'
    // 타임스탬프(19) + 괄호와 공백(3) + "Received: "(10) + 메시지 + 널문자(1)
    size_t log_len = 19 + 3 + 10 + msg_len + 1;
    
    // 메모리 할당
    char *log_entry = (char*)malloc(log_len);
    if (log_entry == NULL) {
        return NULL;
    }
    
    // 로그 문자열 생성
    snprintf(log_entry, log_len, "[%s] Received: %.*s", 
             timestamp, (int)msg_len, msg);
    
    return log_entry;
}