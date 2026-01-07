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
    close(fd);

    // DSA 매개변수 생성 명령어 구성
    char param_command[256];
    snprintf(param_command, sizeof(param_command), "openssl dsaparam -out %s 2048", param_filename);
    
    // DSA 매개변수 생성 실행
    char* param_result = execute_command(param_command);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);
    
    // DSA 개인 키 생성 명령어 구성
    char key_command[256];
    snprintf(key_command, sizeof(key_command), "openssl gendsa %s", param_filename);
    
    // DSA 개인 키 생성 실행
    char* key_result = execute_command(key_command);
    
    // 임시 파일 정리
    remove(param_filename);
    
    return key_result;
}