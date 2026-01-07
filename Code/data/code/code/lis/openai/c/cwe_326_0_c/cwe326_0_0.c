#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령 실행 실패
    }

    char *private_key = NULL;
    size_t key_size = 0;
    ssize_t read;

    // 키의 크기를 알기 위해 읽기
    while ((read = getline(&private_key, &key_size, fp)) != -1) {
        // getline을 통해 키를 모두 읽어오고 있음
    }
    
    pclose(fp);

    if (read == -1) {
        free(private_key);
        return NULL; // 키 생성 실패
    }

    return private_key; // PEM 형식의 RSA 비공개 키 반환
}