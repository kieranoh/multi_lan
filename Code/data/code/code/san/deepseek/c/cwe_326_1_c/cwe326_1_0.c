#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // DSA 키 길이 정의 (2048비트)
    const int key_length = 2048;
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return NULL;
    }
    
    // 파일 디스크립터 닫기 (파일은 여전히 존재함)
    close(fd);
    
    // 1. DSA 매개변수 생성
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        // 매개변수 생성 실패, 임시 파일 정리
        unlink(param_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. DSA 개인 키 생성
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    char* key_result = execute_command(key_cmd);
    
    // 임시 매개변수 파일 정리
    unlink(param_filename);
    
    // 키 생성 결과 반환
    return key_result;
}