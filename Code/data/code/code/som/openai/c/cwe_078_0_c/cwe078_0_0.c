#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어의 출력을 저장할 임시 파일
    FILE *fp;
    char command[256];
    char *result = NULL;
    size_t size = 0;

    // ls -l 명령어 생성
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 명령어의 출력을 동적으로 읽기
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t new_size = size + strlen(buffer) + 1;
        result = realloc(result, new_size);
        if (result == NULL) {
            pclose(fp);
            return ""; // 메모리 할당 실패 시 빈 문자열 반환
        }
        strcat(result, buffer);
        size = new_size - 1; // null terminator를 고려하여 크기 업데이트
    }

    pclose(fp);
    
    // 출력이 없었던 경우 빈 문자열 반환
    if (result == NULL) {
        return "";
    }
    
    return result;
}