#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // 기본 키 길이 설정 (DSA의 경우 일반적으로 1024, 2048, 3072 비트)
    const int key_length = 2048;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return NULL;
    }
    
    // 파일 디스크립터 닫기 (mkstemp가 파일을 열어두므로)
    close(fd);
    
    char* result = NULL;
    char* key_output = NULL;
    
    // 1. DSA 매개변수 생성
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    result = execute_command(param_command);
    if (result) {
        free(result);
        result = NULL;
    } else {
        // 매개변수 생성 실패
        remove(param_filename);
        return NULL;
    }
    
    // 2. DSA 개인 키 생성
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    key_output = execute_command(key_command);
    
    // 임시 파일 정리
    remove(param_filename);
    
    // 키 생성 결과 반환
    return key_output;
}