#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // 기본 키 길이 설정 (일반적으로 2048비트가 안전한 선택)
    const int key_length = 2048;
    
    // 명령어 문자열 구성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프를 통해 명령어 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // PEM 키 데이터 읽기
    char buffer[4096];
    size_t total_size = 0;
    char *pem_key = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *temp = realloc(pem_key, total_size + chunk_size + 1);
        if (temp == NULL) {
            free(pem_key);
            pclose(fp);
            return NULL;
        }
        pem_key = temp;
        memcpy(pem_key + total_size, buffer, chunk_size);
        total_size += chunk_size;
        pem_key[total_size] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(fp);
    if (status != 0 || pem_key == NULL || total_size == 0) {
        free(pem_key);
        return NULL;
    }
    
    // PEM 키가 유효한지 확인 (최소한 BEGIN/END 라인이 있어야 함)
    if (strstr(pem_key, "-----BEGIN") == NULL || strstr(pem_key, "-----END") == NULL) {
        free(pem_key);
        return NULL;
    }
    
    return pem_key;
}