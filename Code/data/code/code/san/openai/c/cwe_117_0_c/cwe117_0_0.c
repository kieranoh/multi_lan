#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256
#define TIMESTAMP_LEN 20

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다.
@param msg 수신된 사용자 메시지.
@return 수신된 메시지에 대한 로그 항목. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL) {
        return NULL;
    }

    char *log_entry = (char *)malloc(MAX_MSG_LEN + TIMESTAMP_LEN + 50);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    // ISO 형식의 타임스탬프 생성
    char timestamp[TIMESTAMP_LEN];
    strftime(timestamp, TIMESTAMP_LEN, "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 항목 생성
    snprintf(log_entry, MAX_MSG_LEN + TIMESTAMP_LEN + 50, "[%s] Received: %s", timestamp, msg);

    return log_entry;
}