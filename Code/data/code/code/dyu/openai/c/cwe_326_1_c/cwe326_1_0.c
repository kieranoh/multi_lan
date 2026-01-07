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
        return NULL; // 임시 파일 생성 실패
    }
    close(fd); // 파일 디스크립터를 닫음

    // DSA 매개변수 생성 명령
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 파일 삭제
        return NULL; // DSA 매개변수 생성 실패
    }

    // DSA 개인 키 생성 명령
    snprintf(command, sizeof(command), "openssl gendsa -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(command);
    
    unlink(param_filename); // 임시 파일 삭제
    return private_key; // 성공적으로 생성된 개인 키 반환
}