#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // 키 길이 설정
    int key_length = 2048; // 기본 키 길이 2048 비트
    // 명령어 버퍼 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // 명령어 실행
    FILE *fp;
    char *private_key = NULL;
    char buffer[4096];

    // 파이프를 통해 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류 발생
    }

    // 실행 결과를 문자열로 복사
    size_t key_size = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t buffer_len = strlen(buffer);
        char *new_key = realloc(private_key, key_size + buffer_len + 1);
        if (new_key == NULL) {
            free(private_key);
            pclose(fp);
            return NULL; // 메모리 할당 오류
        }
        private_key = new_key;
        strcpy(private_key + key_size, buffer);
        key_size += buffer_len;
    }

    // 파이프 종료
    pclose(fp);
    return private_key; // PEM 형식의 키 반환
}