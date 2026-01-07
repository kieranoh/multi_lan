#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 버퍼를 저장할 메모리 할당
    char *buffer = NULL;
    size_t size = 0;
    FILE *fp;

    // 'ls -l' 명령어를 실행
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", dir_path);

    // 명령어의 출력을 읽기 위한 파이프 열기
    fp = popen(command, "r");
    if (fp == NULL) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 출력을 동적으로 할당한 버퍼에 저장
    buffer = malloc(4096); // 4KB의 메모리 할당
    if (buffer == NULL) {
        pclose(fp);
        return ""; // 메모리 할당 실패 시 빈 문자열 반환
    }

    // 출력을 읽어들임
    size_t len = fread(buffer, sizeof(char), 4096 - 1, fp);
    if (len == 0) {
        free(buffer);
        pclose(fp);
        return ""; // 읽은 내용이 없을 경우 빈 문자열 반환
    }

    // 읽은 내용을 null로 종료
    buffer[len] = '\0';

    // 파이프 닫기
    pclose(fp);

    // 결과 반환
    return buffer;
}