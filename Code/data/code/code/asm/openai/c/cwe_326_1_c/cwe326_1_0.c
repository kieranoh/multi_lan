#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 오류 발생 시 NULL 반환
    }
    close(fd);

    // DSA 파라미터 생성
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command_param) == NULL) {
        unlink(param_filename);
        return NULL; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키 생성
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out /dev/stdout %s", param_filename);
    char* dsa_key = execute_command(command_key);

    // 생성된 DSA 파라미터 파일 삭제
    unlink(param_filename);

    return dsa_key; // 생성된 DSA 개인 키 반환
}