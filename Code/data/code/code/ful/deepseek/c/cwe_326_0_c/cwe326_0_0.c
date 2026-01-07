#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* 비공개 RSA 키를 생성하고 PEM 형식으로 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    FILE *pipe = NULL;
    char command[256];
    char *result = NULL;
    size_t buffer_size = 4096;
    size_t total_size = 0;
    size_t bytes_read = 0;
    char buffer[1024];
    
    /* 키 길이를 2048비트로 설정 (보안상 권장되는 최소 길이) */
    const int key_length = 2048;
    
    /* OpenSSL 명령어 구성 */
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    /* 파이프를 통해 OpenSSL 명령어 실행 */
    pipe = popen(command, "r");
    if (!pipe) {
        return NULL;
    }
    
    /* 결과를 저장할 메모리 할당 */
    result = (char *)malloc(buffer_size);
    if (!result) {
        pclose(pipe);
        return NULL;
    }
    result[0] = '\0';
    
    /* 파이프에서 출력 읽기 */
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        bytes_read = strlen(buffer);
        
        /* 필요한 경우 버퍼 크기 확장 */
        if (total_size + bytes_read + 1 > buffer_size) {
            buffer_size *= 2;
            char *temp = (char *)realloc(result, buffer_size);
            if (!temp) {
                free(result);
                pclose(pipe);
                return NULL;
            }
            result = temp;
        }
        
        /* 버퍼 내용 추가 */
        strcat(result, buffer);
        total_size += bytes_read;
    }
    
    /* 파이프 닫기 */
    int status = pclose(pipe);
    
    /* 명령어 실행 실패 또는 빈 결과 확인 */
    if (status != 0 || total_size == 0) {
        free(result);
        return NULL;
    }
    
    /* 결과가 유효한 PEM 형식인지 확인 */
    if (strstr(result, "-----BEGIN PRIVATE KEY-----") == NULL || 
        strstr(result, "-----END PRIVATE KEY-----") == NULL) {
        free(result);
        return NULL;
    }
    
    return result;
}