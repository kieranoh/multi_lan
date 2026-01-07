#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char* create_dsa_key() {
    // 키 길이 정의 (일반적으로 2048 또는 3072 비트)
    const int key_length = 2048;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/keyXXXXXX";
    
    int fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        fprintf(stderr, "Failed to create temporary parameter file: %s\n", strerror(errno));
        return NULL;
    }
    close(fd_param);
    
    int fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        fprintf(stderr, "Failed to create temporary key file: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // 1. DSA 매개변수 생성
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        fprintf(stderr, "Failed to execute DSA parameter generation command\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. DSA 개인 키 생성
    char key_cmd[512];
    snprintf(key_cmd, sizeof(key_cmd), "openssl gendsa %s 2>&1", param_filename);
    
    char* key_gen_output = execute_command(key_cmd);
    if (key_gen_output == NULL) {
        fprintf(stderr, "Failed to execute DSA key generation command\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 키 생성 출력에서 PEM 형식의 키 추출
    // openssl gendsa는 표준 출력에 PEM 키를 출력합니다
    char* pem_key = NULL;
    
    // 출력이 비어있지 않은지 확인
    if (strlen(key_gen_output) > 0) {
        // 키 출력을 문자열로 복사
        pem_key = strdup(key_gen_output);
        if (pem_key == NULL) {
            fprintf(stderr, "Memory allocation failed for PEM key\n");
        }
    } else {
        fprintf(stderr, "DSA key generation produced empty output\n");
    }
    
    free(key_gen_output);
    
    // 임시 파일 정리
    unlink(param_filename);
    unlink(key_filename);
    
    // 생성된 PEM 키가 유효한지 확인
    if (pem_key != NULL) {
        // PEM 키 형식 확인 (-----BEGIN DSA PRIVATE KEY-----로 시작해야 함)
        if (strstr(pem_key, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
            fprintf(stderr, "Generated key does not appear to be in valid PEM format\n");
            free(pem_key);
            return NULL;
        }
    }
    
    return pem_key;
}