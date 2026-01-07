#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령의 출력 결과를 저장할 버퍼 크기 정의
    const int buffer_size = 1024;
    char buffer[buffer_size];
    FILE *fp;
    char *result = NULL;
    size_t result_size = 0;

    // 실행할 명령어를 담은 문자열 생성
    char command[buffer_size];
    snprintf(command, sizeof(command), "ls -l %s 2>/dev/null", dir_path);

    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 명령어의 출력을 읽어 결과를 저장
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t buffer_len = strlen(buffer);
        char *new_result = realloc(result, result_size + buffer_len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // 메모리 할당 오류 발생 시 빈 문자열 반환
        }
        result = new_result;
        strcpy(result + result_size, buffer);
        result_size += buffer_len;
    }

    // 명령어 실행 종료
    pclose(fp);
    return result; // 결과 문자열 반환
}