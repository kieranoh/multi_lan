#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 실행합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 오류 발생
    }
    close(fd);

    // DSA 매개변수 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename);
        return NULL; // 오류 발생
    }

    // DSA 개인 키 생성
    char* key_command = (char*)malloc(256);
    snprintf(key_command, 256, "openssl gendsa -out %s %s", param_filename, param_filename);
    char* key_output = execute_command(key_command);
    free(key_command);

    // 임시 파일 삭제
    unlink(param_filename);

    return key_output; // PEM 형식의 DSA 개인 키 반환
}