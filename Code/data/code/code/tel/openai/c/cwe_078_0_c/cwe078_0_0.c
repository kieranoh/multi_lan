#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 커맨드 실행을 위한 버퍼와 결과를 받을 문자열 초기화
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);
    
    // 파이프를 열고 명령의 출력을 읽기 위한 변수
    FILE *fp;
    char *result = NULL;
    size_t size = 0;
    ssize_t read;

    // 파이프를 통해 ls -l 명령 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 결과를 읽어들일 임시 버퍼
    char buffer[1024];
    size_t total_length = 0;

    // 결과를 계속 읽어서 동적으로 메모리에 저장
    while ((read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        char *new_result = realloc(result, total_length + read + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return ""; // 메모리 할당 실패 시 빈 문자열 반환
        }
        result = new_result;
        memcpy(result + total_length, buffer, read);
        total_length += read;
    }

    // 널 종료
    if (result) {
        result[total_length] = '\0';
    }

    // 파이프 닫기
    pclose(fp);

    // 결과 반환
    return result;
}