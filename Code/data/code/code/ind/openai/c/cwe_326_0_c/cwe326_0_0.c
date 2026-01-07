#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048;
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령 실행 실패
    }

    // 결과를 저장할 버퍼 할당
    char *private_key = malloc(4096); // 충분한 크기의 메모리 할당
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패
    }

    // 명령의 출력을 읽기
    size_t bytes_read = fread(private_key, 1, 4095, fp);
    private_key[bytes_read] = '\0'; // null 종료

    pclose(fp);

    return private_key; // 생성된 키 반환
}