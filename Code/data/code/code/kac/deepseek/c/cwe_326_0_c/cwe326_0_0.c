#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    FILE *pipe = NULL;
    char *key = NULL;
    char command[256];
    size_t key_size = 0;
    size_t buffer_size = 1024;
    size_t total_read = 0;
    char buffer[1024];
    ssize_t bytes_read;
    
    // 기본 키 길이를 2048비트로 설정
    int key_length = 2048;
    
    // 명령어 생성
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프를 통해 openssl 명령어 실행
    pipe = popen(command, "r");
    if (pipe == NULL) {
        return NULL;
    }
    
    // 키 메모리 할당
    key = (char *)malloc(buffer_size);
    if (key == NULL) {
        pclose(pipe);
        return NULL;
    }
    key[0] = '\0';
    
    // 출력 읽기
    while ((bytes_read = fread(buffer, 1, sizeof(buffer) - 1, pipe)) > 0) {
        // 필요한 경우 버퍼 확장
        if (total_read + bytes_read + 1 > buffer_size) {
            buffer_size *= 2;
            char *new_key = (char *)realloc(key, buffer_size);
            if (new_key == NULL) {
                free(key);
                pclose(pipe);
                return NULL;
            }
            key = new_key;
        }
        
        // 버퍼 내용 복사
        memcpy(key + total_read, buffer, bytes_read);
        total_read += bytes_read;
        key[total_read] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(pipe);
    
    // 명령어 실패 확인
    if (status != 0 || total_read == 0) {
        free(key);
        return NULL;
    }
    
    // 키가 유효한지 확인 (PEM 형식인지)
    if (strstr(key, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(key, "-----END PRIVATE KEY-----") == NULL) {
        free(key);
        return NULL;
    }
    
    return key;
}