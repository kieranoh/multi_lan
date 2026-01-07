#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    FILE *fp;
    char *buffer = NULL;
    size_t size = 0;

    // 파이프를 열어 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류 발생 시 NULL 반환
    }

    // 결과를 읽어들이기 위한 버퍼 크기 조정
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    fread(buffer, 1, size, fp);
    buffer[size] = '\0'; // 문자열 종료

    pclose(fp);
    return buffer; // PEM 형식의 RSA 비공개 키 반환
}