#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 명령어를 저장할 버퍼
    char command[256];
    // 결과를 저장할 버퍼
    char *output = malloc(4096);
    if (output == NULL) {
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }
    // 출력 버퍼 초기화
    output[0] = '\0';

    // 디렉토리 경로를 포함한 ls -l 명령어 생성
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // 명령어 실행을 위한 파이프 생성
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        free(output); // 메모리 해제
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 명령어 출력 읽기
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // 출력에 추가
        strncat(output, buffer, 4096 - strlen(output) - 1);
    }

    // 파이프 닫기
    pclose(fp);
    return output; // 결과 반환
}