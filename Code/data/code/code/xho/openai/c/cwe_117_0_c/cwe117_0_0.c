#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG_LEN 256

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 '[<timestamp_iso_format>] Received: <msg>' 형식으로 생성합니다. */
char* generate_receive_log(const char *msg) {
    if (msg == NULL || strlen(msg) > MAX_MSG_LEN) {
        return NULL; // 오류 처리
    }

    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // ISO 형식의 타임스탬프 문자열 생성
    char timestamp[20]; // YYYY-MM-DDTHH:MM:SS 형식
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    // 로그 문자열 길이 계산
    size_t log_length = strlen(timestamp) + strlen(msg) + 18; // '[<timestamp>] Received: ' 의 길이

    // 결과 문자열 할당
    char *log_entry = (char *)malloc(log_length);
    if (log_entry == NULL) {
        return NULL; // 메모리 할당 실패 처리
    }

    // 로그 항목 생성
    snprintf(log_entry, log_length, "[%s] Received: %s", timestamp, msg);

    return log_entry; // 로그 항목 반환
}