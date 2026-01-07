#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    DSA *dsa = NULL;
    BIO *bio = NULL;
    char *key_str = NULL;
    long key_size;
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = -1;
    char command[256];
    char *result = NULL;
    
    // 임시 파일 생성
    fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // DSA 매개변수 생성 명령 실행
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    result = execute_command(command);
    if (result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(result);
    
    // DSA 개인 키 생성 명령 실행
    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    result = execute_command(command);
    if (result == NULL) {
        remove(param_filename);
        return NULL;
    }
    
    // 결과 문자열 저장
    key_str = result;
    
    // 임시 파일 정리
    remove(param_filename);
    
    return key_str;
}