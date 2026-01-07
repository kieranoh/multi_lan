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
        return NULL; // 오류가 발생한 경우
    }
    close(fd); // 이제 파일 디스크립터를 닫습니다.

    // DSA 매개변수 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 파일 삭제
        return NULL; // 오류가 발생한 경우
    }

    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa -out %s -rand /dev/urandom %s", param_filename, param_filename);
    char* private_key = execute_command(command);
    
    // 매개변수 파일 삭제
    unlink(param_filename);
    
    return private_key; // PEM 형식의 DSA 개인 키 반환
}