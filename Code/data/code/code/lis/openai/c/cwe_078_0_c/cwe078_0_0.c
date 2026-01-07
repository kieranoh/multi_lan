#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어를 실행할 파이프를 엽니다.
    FILE *fp;
    char command[256];
    char *result = NULL;
    size_t size = 0;

    // ls -l 명령어와 디렉토리 경로를 결합합니다.
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // 명령어를 실행하고 결과를 읽기 위해 파이프를 엽니다.
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 명령어의 출력을 읽어들입니다.
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, size + len + 1); // 결과를 재할당
        if (new_result == NULL) {
            free(result); // 메모리 해제
            pclose(fp);
            return ""; // 메모리 할당 오류 발생 시 빈 문자열 반환
        }
        result = new_result;
        strcpy(result + size, buffer);
        size += len;
    }

    // 파이프 닫기
    pclose(fp);

    // 결과가 없으면 빈 문자열 반환
    if (result == NULL) {
        return "";
    }

    return result;
}