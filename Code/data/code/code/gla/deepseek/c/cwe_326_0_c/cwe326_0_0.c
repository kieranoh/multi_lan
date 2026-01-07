#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // 기본 키 길이 설정 (일반적으로 2048비트가 안전한 표준)
    const int key_length = 2048;
    
    // 명령어를 구성하기 위한 버퍼
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 명령어 실행을 위한 파이프 열기
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // PEM 키 데이터를 읽기 위한 버퍼
    char *key_buffer = NULL;
    size_t buffer_size = 0;
    size_t total_size = 0;
    char temp_buffer[1024];
    
    // 명령어 출력 읽기
    while (fgets(temp_buffer, sizeof(temp_buffer), fp) != NULL) {
        size_t chunk_size = strlen(temp_buffer);
        
        // 버퍼 재할당
        char *new_buffer = realloc(key_buffer, total_size + chunk_size + 1);
        if (new_buffer == NULL) {
            free(key_buffer);
            pclose(fp);
            return NULL;
        }
        
        key_buffer = new_buffer;
        memcpy(key_buffer + total_size, temp_buffer, chunk_size);
        total_size += chunk_size;
        key_buffer[total_size] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(fp);
    
    // 명령어 실행 실패 또는 키 생성 실패 확인
    if (status != 0 || key_buffer == NULL || total_size == 0) {
        free(key_buffer);
        return NULL;
    }
    
    // 키 데이터가 유효한 PEM 형식인지 확인
    if (strstr(key_buffer, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(key_buffer, "-----END PRIVATE KEY-----") == NULL) {
        free(key_buffer);
        return NULL;
    }
    
    return key_buffer;
}