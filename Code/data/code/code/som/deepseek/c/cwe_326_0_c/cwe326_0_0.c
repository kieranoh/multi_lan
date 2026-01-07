#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // 키 길이 정의 (일반적으로 2048 또는 4096 비트)
    const int key_length = 2048;
    
    // 명령어 문자열 구성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프를 통해 openssl 명령어 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // PEM 키 데이터 읽기
    char buffer[4096];
    size_t total_size = 0;
    char *key_data = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *new_key_data = realloc(key_data, total_size + chunk_size + 1);
        if (new_key_data == NULL) {
            free(key_data);
            pclose(fp);
            return NULL;
        }
        key_data = new_key_data;
        memcpy(key_data + total_size, buffer, chunk_size);
        total_size += chunk_size;
        key_data[total_size] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(fp);
    if (status != 0 || total_size == 0) {
        free(key_data);
        return NULL;
    }
    
    // 키 데이터가 유효한지 확인 (PEM 형식인지)
    if (key_data != NULL && strstr(key_data, "-----BEGIN PRIVATE KEY-----") == NULL) {
        free(key_data);
        return NULL;
    }
    
    return key_data;
}