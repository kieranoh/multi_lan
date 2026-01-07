#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령어 실행 실패
    }

    // 출력된 키를 저장할 버퍼
    char *key = NULL;
    size_t key_size = 0;
    ssize_t read;

    // 키를 읽어오기
    while ((read = getline(&key, &key_size, fp)) != -1) {
        // 키 읽기
    }

    pclose(fp);
    
    // 키가 생성되지 않았다면 NULL 반환
    if (key == NULL) {
        return NULL;
    }

    return key; // PEM 형식의 RSA 비공개 키 반환
}