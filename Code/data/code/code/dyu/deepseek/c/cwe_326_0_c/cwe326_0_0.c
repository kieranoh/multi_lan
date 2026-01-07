#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    FILE *fp;
    char command[256];
    char *key = NULL;
    size_t key_size = 0;
    size_t buffer_size = 4096;
    size_t total_read = 0;
    char buffer[1024];
    
    // 기본 키 길이를 2048비트로 설정
    int key_length = 2048;
    
    // OpenSSL 명령어 구성
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 출력 읽기 위한 메모리 할당
    key = (char *)malloc(buffer_size);
    if (key == NULL) {
        pclose(fp);
        return NULL;
    }
    
    // OpenSSL 출력 읽기
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t bytes_read = strlen(buffer);
        
        // 필요시 버퍼 확장
        if (total_read + bytes_read + 1 > buffer_size) {
            buffer_size *= 2;
            char *new_key = (char *)realloc(key, buffer_size);
            if (new_key == NULL) {
                free(key);
                pclose(fp);
                return NULL;
            }
            key = new_key;
        }
        
        // 버퍼에 데이터 복사
        memcpy(key + total_read, buffer, bytes_read);
        total_read += bytes_read;
    }
    
    // 파일 끝에 null 종료자 추가
    if (total_read < buffer_size) {
        key[total_read] = '\0';
    } else {
        // 버퍼가 가득 찬 경우 확장
        char *new_key = (char *)realloc(key, total_read + 1);
        if (new_key == NULL) {
            free(key);
            pclose(fp);
            return NULL;
        }
        key = new_key;
        key[total_read] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(fp);
    if (status != 0) {
        free(key);
        return NULL;
    }
    
    // 키가 비어있는지 확인
    if (total_read == 0 || key[0] == '\0') {
        free(key);
        return NULL;
    }
    
    return key;
}