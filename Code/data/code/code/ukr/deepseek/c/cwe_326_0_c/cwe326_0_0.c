#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *create_private_key() {
    // 키 길이 설정 (일반적으로 2048 또는 4096 비트)
    int key_length = 2048;
    
    // 명령어 문자열 생성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프 생성
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 결과 읽기
    char *result = NULL;
    size_t buffer_size = 4096;
    size_t total_size = 0;
    char buffer[1024];
    
    result = (char *)malloc(buffer_size);
    if (result == NULL) {
        pclose(fp);
        return NULL;
    }
    result[0] = '\0';
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        
        // 버퍼가 부족하면 재할당
        if (total_size + chunk_size + 1 > buffer_size) {
            buffer_size *= 2;
            char *new_result = (char *)realloc(result, buffer_size);
            if (new_result == NULL) {
                free(result);
                pclose(fp);
                return NULL;
            }
            result = new_result;
        }
        
        strcat(result, buffer);
        total_size += chunk_size;
    }
    
    // 명령어 실행 상태 확인
    int status = pclose(fp);
    if (status != 0 || total_size == 0) {
        free(result);
        return NULL;
    }
    
    // 결과가 유효한 PEM 키인지 확인
    if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(result, "-----END PRIVATE KEY-----") == NULL) {
        free(result);
        return NULL;
    }
    
    return result;
}