#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 이전에 제공된 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 오류: 임시 파일 생성 실패
    }
    close(fd); // 파일 디스크립터를 닫습니다.

    // DSA 매개변수를 생성
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    
    if (execute_command(command_param) == NULL) {
        unlink(param_filename); // 파일 제거
        return NULL; // 오류: 매개변수 생성 실패
    }

    // DSA 개인 키를 생성
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command_key);
    
    unlink(param_filename); // 임시 파일 제거

    return private_key; // 생성된 개인 키를 반환
}