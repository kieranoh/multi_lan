#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // RSA 키 길이 설정
    int key_length = 2048; // 일반적으로 2048 비트 또는 4096 비트 사용
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // 명령어 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령어 실행 실패
    }

    // 결과를 저장할 버퍼
    char *buffer = NULL;
    size_t size = 0;

    // 결과를 읽고 문자열로 저장
    ssize_t bytes_read = getdelim(&buffer, &size, EOF, fp);
    pclose(fp);

    if (bytes_read == -1) {
        free(buffer);
        return NULL; // 읽기 실패
    }

    return buffer; // PEM 형식의 RSA 비공개 키 반환
}