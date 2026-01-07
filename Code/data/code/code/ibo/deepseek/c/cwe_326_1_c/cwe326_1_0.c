#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // 파일 디스크립터 닫기 (mkstemp가 파일을 열어두므로)

    // 키 길이 설정 (일반적으로 1024 또는 2048)
    int key_length = 1024;

    // 1. DSA 매개변수 생성
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* param_result = execute_command(param_command);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);

    // 2. DSA 개인 키 생성
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s", param_filename);
    
    char* key_result = execute_command(key_command);
    
    // 임시 파일 정리
    remove(param_filename);

    return key_result;
}