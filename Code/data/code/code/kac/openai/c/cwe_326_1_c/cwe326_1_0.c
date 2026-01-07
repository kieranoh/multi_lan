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
    close(fd); // 파일 디스크립터 닫기
    
    // DSA 매개변수 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 오류 발생 시 임시 파일 삭제
        return NULL;
    }
    
    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command);
    
    // 임시 파일 삭제
    unlink(param_filename);
    
    return private_key;
}