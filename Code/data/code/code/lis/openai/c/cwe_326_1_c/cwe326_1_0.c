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
        return NULL; // 오류 처리
    }
    
    // DSA 매개변수 파일 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename);
        return NULL; // 오류 처리
    }
    
    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* dsa_key = execute_command(command);
    
    // 임시 파일 닫기 및 삭제
    close(fd);
    unlink(param_filename);
    
    return dsa_key; // 생성된 DSA 개인 키 반환
}