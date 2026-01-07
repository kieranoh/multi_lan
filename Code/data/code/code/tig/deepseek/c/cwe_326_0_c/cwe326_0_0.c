#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    const int key_length = 2048;
    char command[256];
    FILE *pipe;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_capacity = 1024;
    char buffer[1024];
    size_t bytes_read;
    
    // 명령어 생성
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프를 통해 명령어 실행
    pipe = popen(command, "r");
    if (pipe == NULL) {
        return NULL;
    }
    
    // 결과를 저장할 메모리 할당
    result = (char *)malloc(result_capacity);
    if (result == NULL) {
        pclose(pipe);
        return NULL;
    }
    result[0] = '\0';
    
    // 파이프에서 데이터 읽기
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), pipe)) > 0) {
        // 필요한 경우 메모리 확장
        if (result_size + bytes_read + 1 > result_capacity) {
            result_capacity = (result_size + bytes_read + 1) * 2;
            char *temp = (char *)realloc(result, result_capacity);
            if (temp == NULL) {
                free(result);
                pclose(pipe);
                return NULL;
            }
            result = temp;
        }
        
        // 데이터 복사
        memcpy(result + result_size, buffer, bytes_read);
        result_size += bytes_read;
        result[result_size] = '\0';
    }
    
    // 파이프 닫기
    int status = pclose(pipe);
    
    // 명령어 실행 실패 또는 빈 결과 확인
    if (status != 0 || result_size == 0) {
        free(result);
        return NULL;
    }
    
    // 결과가 PEM 형식인지 확인 (기본적인 검증)
    if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(result, "-----END PRIVATE KEY-----") == NULL) {
        free(result);
        return NULL;
    }
    
    return result;
}