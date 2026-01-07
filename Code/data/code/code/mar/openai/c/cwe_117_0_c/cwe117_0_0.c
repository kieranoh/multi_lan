#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL || strlen(msg) >= MAX_MSG_LEN) {
        return NULL; // 입력 메시지가 NULL이거나 최대 길이를 초과하는 경우 NULL 반환
    }

    time_t now;
    struct tm *tm_info;
    char timestamp[20]; // ISO 8601 형식(YYYY-MM-DDTHH:MM:SS)
    char *log_entry;

    // 현재 시간 가져오기
    time(&now);
    tm_info = localtime(&now);

    // 시간 포맷팅
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 항목 길이 계산
    size_t log_length = strlen(timestamp) + strlen(msg) + 20; // 포맷 문자열 및 널 종료자
    log_entry = (char *)malloc(log_length);

    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패
    }

    // 로그 형식 작성
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);

    return log_entry; // 생성된 로그 항목 반환
}