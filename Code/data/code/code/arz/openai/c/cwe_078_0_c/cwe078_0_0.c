#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_ls_result(const char *dir_path) {
    FILE *fp;
    char *result = malloc(BUFFER_SIZE);
    if (result == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }
    
    // 명령어를 실행하기 위한 버퍼
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        free(result);
        return ""; // popen 실패 시 빈 문자열 반환
    }

    // 결과를 읽어들이기
    size_t len = 0;
    while (fgets(result + len, BUFFER_SIZE - len, fp) != NULL) {
        len += strlen(result + len);
        if (len >= BUFFER_SIZE - 1) {
            break; // 버퍼 크기 초과 방지
        }
    }
    
    // 파이프 종료
    pclose(fp);

    return result;
}