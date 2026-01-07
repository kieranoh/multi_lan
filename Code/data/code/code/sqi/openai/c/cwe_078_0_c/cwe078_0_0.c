#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 커맨드 버퍼와 결과 버퍼를 위한 공간 할당
    char command[256];
    char *result = malloc(1024 * sizeof(char)); // 결과 저장을 위한 메모리 할당
    if (!result) {
        return ""; // 메모리 할당 실패시 빈 문자열 반환
    }

    // 커맨드 문자열 구성
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // 파이프를 통해 커맨드 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // 명령 실행 실패시 빈 문자열 반환
    }

    // 결과를 읽어들임
    size_t n = 0;
    ssize_t read;
    while ((read = getline(&result, &n, fp)) != -1) {
        // 결과가 너무 크면 동적 메모리 할당을 늘리기
        if (n > 1024) {
            result = realloc(result, n);
        }
    }

    // 파이프 종료
    pclose(fp);

    return result; // 결과 반환
}