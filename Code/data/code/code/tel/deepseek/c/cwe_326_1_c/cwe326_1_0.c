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
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return NULL;
    }
    close(fd);
    
    // DSA 매개변수 생성 명령
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), "openssl dsaparam -out %s 2048", param_filename);
    
    char *param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        unlink(param_filename);
        return NULL;
    }
    free(param_result);
    
    // DSA 개인 키 생성 명령
    char key_cmd[512];
    snprintf(key_cmd, sizeof(key_cmd), "openssl gendsa %s 2>/dev/null", param_filename);
    
    char *key_result = execute_command(key_cmd);
    if (key_result == NULL) {
        unlink(param_filename);
        return NULL;
    }
    
    // 임시 파일 정리
    unlink(param_filename);
    
    // 결과 문자열 반환
    return key_result;
}