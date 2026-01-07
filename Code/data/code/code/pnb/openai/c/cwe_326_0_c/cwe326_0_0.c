#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // RSA 키의 لمبائی
    int key_length = 2048; // 2048 비트 키
    char command[128];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // 명령을 실행하고 결과를 가져옵니다.
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령 실행 실패
    }

    // 결과를 읽어옵니다.
    if (getline(&buffer, &size, fp) == -1) {
        pclose(fp);
        return NULL; // 결과 읽기 실패
    }
    
    pclose(fp);
    return buffer; // PEM 형식의 RSA 비공개 키 반환
}