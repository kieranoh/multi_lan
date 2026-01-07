#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // 키 길이 정의 (DSA의 경우 일반적으로 1024, 2048, 3072 비트)
    const int key_length = 2048;
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL;
    }
    
    // 파일 디스크립터 닫기 (파일은 여전히 존재함)
    close(fd);
    
    // DSA 매개변수 생성 명령어 구성
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    // DSA 매개변수 생성 실행
    char* param_result = execute_command(param_command);
    if (param_result) {
        free(param_result);
    } else {
        // 매개변수 생성 실패 시 임시 파일 삭제
        remove(param_filename);
        return NULL;
    }
    
    // DSA 개인 키 생성 명령어 구성
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    // DSA 개인 키 생성 실행
    char* key_result = execute_command(key_command);
    
    // 임시 매개변수 파일 삭제
    remove(param_filename);
    
    // 키 생성 결과 반환
    return key_result;
}