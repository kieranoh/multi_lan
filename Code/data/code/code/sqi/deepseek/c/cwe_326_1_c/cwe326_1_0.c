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
    char *command = NULL;
    char *result = NULL;
    
    // 임시 파일 생성
    fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // DSA 매개변수 생성 명령 실행
    command = malloc(strlen("openssl dsaparam -out ") + strlen(param_filename) + strlen(" 2048") + 1);
    if (!command) {
        unlink(param_filename);
        return NULL;
    }
    sprintf(command, "openssl dsaparam -out %s 2048", param_filename);
    
    result = execute_command(command);
    free(command);
    if (!result) {
        unlink(param_filename);
        return NULL;
    }
    free(result);
    
    // DSA 개인 키 생성 명령 실행
    command = malloc(strlen("openssl gendsa ") + strlen(param_filename) + 1);
    if (!command) {
        unlink(param_filename);
        return NULL;
    }
    sprintf(command, "openssl gendsa %s", param_filename);
    
    result = execute_command(command);
    free(command);
    if (!result) {
        unlink(param_filename);
        return NULL;
    }
    
    // 임시 파일 삭제
    unlink(param_filename);
    
    // 결과 문자열 복사
    key_str = malloc(strlen(result) + 1);
    if (!key_str) {
        free(result);
        return NULL;
    }
    strcpy(key_str, result);
    free(result);
    
    return key_str;
}