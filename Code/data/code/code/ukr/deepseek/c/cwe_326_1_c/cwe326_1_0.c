#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // 키 길이 정의 (일반적으로 2048 또는 3072 비트)
    const char* key_length = "2048";
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL;
    }
    
    // 파일 디스크립터 닫기 (mkstemp는 파일을 열어두므로)
    close(fd);
    
    // 1단계: DSA 매개변수 생성
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), 
             "openssl dsaparam -out %s %s 2>/dev/null", 
             param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);
    
    // 2단계: DSA 개인 키 생성
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    char* key_result = execute_command(key_cmd);
    
    // 임시 파일 정리
    remove(param_filename);
    
    // 키 생성 결과 확인
    if (key_result == NULL || strlen(key_result) == 0) {
        if (key_result != NULL) {
            free(key_result);
        }
        return NULL;
    }
    
    return key_result;
}