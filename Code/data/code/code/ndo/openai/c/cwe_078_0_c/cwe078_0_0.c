#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 결과를 저장할 동적 메모리 할당
    char *result = NULL;
    size_t result_size = 0;
    FILE *fp;
    char buffer[1024]; // 버퍼 크기

    // 명령어 형식화
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // 명령 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 결과를 읽어들여 동적 메모리에 저장
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, result_size + len + 1);
        if (new_result == NULL) {
            free(result); // 메모리 해제
            pclose(fp);
            return ""; // 오류 발생 시 빈 문자열 반환
        }
        result = new_result;
        strcpy(result + result_size, buffer);
        result_size += len;
    }

    // 명령어 실행 종료
    pclose(fp);
    
    // 결과 반환
    return result; 
}