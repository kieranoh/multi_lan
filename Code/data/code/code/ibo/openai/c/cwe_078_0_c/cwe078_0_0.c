#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어 출력 저장을 위한 파이프와 버퍼 초기화
    FILE *fp;
    char path[1035];
    char *result = NULL;
    size_t result_size = 0;

    // ls -l 명령 실행
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);
    
    // 명령어의 결과를 읽기 위한 파이프 오픈
    fp = popen(command, "r");
    if (fp == NULL) {
        return "";  // 오류 발생 시 빈 문자열 반환
    }

    // 결과를 동적으로 할당된 메모리에 저장
    while (fgets(path, sizeof(path), fp) != NULL) {
        size_t len = strlen(path);
        char *new_result = realloc(result, result_size + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return "";  // 메모리 할당 실패 시 빈 문자열 반환
        }
        result = new_result;
        strcpy(result + result_size, path);
        result_size += len;
    }

    // 파이프 닫기
    pclose(fp);
    
    // 결과가 없으면 빈 문자열 반환
    if (result == NULL) {
        return "";
    }

    return result;  // 결과 반환
}