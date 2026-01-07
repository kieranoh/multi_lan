#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어와 크기를 정의합니다.
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // 파이프를 열기 위한 FILE 포인터
    FILE *fp;
    char *result = NULL;
    size_t result_size = 0;
    size_t read_size;

    // 명령을 실행하고 출력을 파이프에 연결합니다.
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 명령의 출력을 읽습니다.
    char buffer[256];
    while ((read_size = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        // 결과 버퍼의 크기를 조정합니다.
        char *temp = realloc(result, result_size + read_size + 1);
        if (temp == NULL) {
            free(result);
            pclose(fp);
            return ""; // 메모리 할당 실패 시 빈 문자열 반환
        }
        result = temp;

        // 읽은 데이터를 결과에 추가합니다.
        memcpy(result + result_size, buffer, read_size);
        result_size += read_size;
    }

    // 결과 문자열의 끝에 널 종료 문자를 추가합니다.
    if (result != NULL) {
        result[result_size] = '\0';
    }

    // 파이프를 닫고 결과 반환
    pclose(fp);
    return result ? result : ""; // 결과가 NULL이면 빈 문자열 반환
}