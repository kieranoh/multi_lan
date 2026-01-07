#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 커맨드의 결과를 저장할 버퍼 크기
    const size_t buffer_size = 256;
    char command[buffer_size];
    FILE *fp;
    char *result = NULL;
    size_t result_size = 0;

    // ls -l 명령어를 위한 커맨드 문자열 생성
    snprintf(command, sizeof(command), "ls -l \"%s\"", dir_path);

    // 커맨드를 실행하고 결과를 읽기 위한 파이프 열기
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류가 발생하면 빈 문자열 반환
    }

    // 결과를 동적으로 저장하기 위한 초기 메모리 할당
    result = malloc(buffer_size);
    if (result == NULL) {
        pclose(fp);
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 결과 읽기
    while (fgets(result + result_size, buffer_size - result_size, fp) != NULL) {
        result_size += strlen(result + result_size);
        // 더 많은 메모리가 필요하면 재할당
        if (result_size >= buffer_size - 1) {
            buffer_size *= 2;
            char *temp = realloc(result, buffer_size);
            if (temp == NULL) {
                free(result);
                pclose(fp);
                return ""; // 재할당 실패 시 빈 문자열 반환
            }
            result = temp;
        }
    }

    // 파이프 닫기
    if (pclose(fp) == -1) {
        free(result);
        return ""; // pclose 실패 시 빈 문자열 반환
    }

    return result; // 결과 반환
}