#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    /* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
    명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.
    
    @return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
    
    FILE *fp;
    char command[256];
    char *key_buffer = NULL;
    size_t buffer_size = 4096;  // 초기 버퍼 크기
    size_t key_length = 0;
    size_t total_read = 0;
    int ch;
    
    // 키 길이 설정 (일반적으로 2048 또는 4096 비트)
    int rsa_key_length = 2048;
    
    // OpenSSL 명령어 생성
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             rsa_key_length);
    
    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 버퍼 할당
    key_buffer = (char *)malloc(buffer_size);
    if (key_buffer == NULL) {
        pclose(fp);
        return NULL;
    }
    
    // OpenSSL 출력 읽기
    while ((ch = fgetc(fp)) != EOF) {
        // 버퍼가 부족하면 크기 확장
        if (total_read >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_buffer = (char *)realloc(key_buffer, buffer_size);
            if (new_buffer == NULL) {
                free(key_buffer);
                pclose(fp);
                return NULL;
            }
            key_buffer = new_buffer;
        }
        
        key_buffer[total_read++] = (char)ch;
    }
    
    // 파일 포인터 닫기
    int pclose_result = pclose(fp);
    if (pclose_result != 0) {
        // OpenSSL 명령어 실패
        free(key_buffer);
        return NULL;
    }
    
    // 문자열 종료
    if (total_read == 0) {
        free(key_buffer);
        return NULL;
    }
    
    key_buffer[total_read] = '\0';
    
    // PEM 형식인지 확인 (기본적인 검증)
    if (strstr(key_buffer, "-----BEGIN PRIVATE KEY-----") == NULL ||
        strstr(key_buffer, "-----END PRIVATE KEY-----") == NULL) {
        free(key_buffer);
        return NULL;
    }
    
    return key_buffer;
}