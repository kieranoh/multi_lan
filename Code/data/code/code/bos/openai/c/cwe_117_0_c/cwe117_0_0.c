#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MSG_LEN 256

char* generate_receive_log(const char *msg) {
    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    // ISO 8601 형식으로 타임스탬프 문자열 생성
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", t);

    // 로그 메시지 생성
    char *log_entry = malloc(strlen(timestamp) + strlen(msg) + 40); // 40은 추가적인 포맷팅을 위한 공간
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 로그 항목 포맷팅
    sprintf(log_entry, "[%s] Received: %s", timestamp, msg);

    return log_entry; // 생성된 로그 항목 반환
}