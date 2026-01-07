#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령 실행 실패
    }

    // 결과를 읽기 위한 버퍼
    char *output = NULL;
    size_t len = 0;
    ssize_t read;

    // 명령의 출력 크기를 측정
    while ((read = getline(&output, &len, fp)) != -1) {
        // 아무 작업도 하지 않음, 단순히 읽습니다.
    }

    pclose(fp);

    // 읽은 내용이 없으면 NULL 반환
    if (output == NULL || strlen(output) == 0) {
        return NULL;
    }

    return output; // PEM 형식의 RSA 개인 키 반환
}