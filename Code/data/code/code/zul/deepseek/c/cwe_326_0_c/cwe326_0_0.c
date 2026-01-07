#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    /* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
    명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.
    
    @return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
    
    // 키 길이 정의 (일반적으로 2048 또는 4096 비트 사용)
    const int key_length = 2048;
    
    // 명령어 문자열 구성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 명령어 실행 및 결과 읽기
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    // 결과를 저장할 버퍼
    char *key_buffer = NULL;
    size_t buffer_size = 0;
    size_t total_size = 0;
    
    // 임시 버퍼
    char temp_buffer[1024];
    size_t bytes_read;
    
    // 명령어 출력 읽기
    while ((bytes_read = fread(temp_buffer, 1, sizeof(temp_buffer), fp)) > 0) {
        // 버퍼 재할당
        char *new_buffer = realloc(key_buffer, total_size + bytes_read + 1);
        if (new_buffer == NULL) {
            free(key_buffer);
            pclose(fp);
            return NULL;
        }
        
        key_buffer = new_buffer;
        
        // 데이터 복사
        memcpy(key_buffer + total_size, temp_buffer, bytes_read);
        total_size += bytes_read;
    }
    
    // 파일 포인터 닫기
    int status = pclose(fp);
    
    // 명령어 실패 확인
    if (status != 0 || total_size == 0) {
        free(key_buffer);
        return NULL;
    }
    
    // 문자열 종료
    if (key_buffer != NULL) {
        key_buffer[total_size] = '\0';
    }
    
    return key_buffer;
}