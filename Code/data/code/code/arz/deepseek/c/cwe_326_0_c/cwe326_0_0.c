#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *create_private_key() {
    // 기본 키 길이 설정 (일반적으로 2048비트가 안전한 선택)
    int key_length = 2048;
    
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
    
    // 출력 읽기
    char buffer[4096];
    size_t total_size = 0;
    char *result = NULL;
    
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t chunk_size = strlen(buffer);
        char *new_result = realloc(result, total_size + chunk_size + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return NULL;
        }
        result = new_result;
        memcpy(result + total_size, buffer, chunk_size);
        total_size += chunk_size;
        result[total_size] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(fp);
    if (status != 0) {
        free(result);
        return NULL;
    }
    
    // 결과가 비어있는지 확인
    if (result == NULL || strlen(result) == 0) {
        free(result);
        return NULL;
    }
    
    return result;
}