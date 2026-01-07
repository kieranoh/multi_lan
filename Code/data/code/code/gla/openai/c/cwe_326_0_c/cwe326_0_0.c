#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // 파이프를 사용하여 openssl 명령어 실행
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        return NULL; // 파이프 생성 실패 시 NULL 반환
    }

    // 결과를 저장할 버퍼 할당
    char *private_key = malloc(4096); // 충분히 큰 버퍼 할당
    if (!private_key) {
        pclose(pipe);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 키 데이터를 버퍼에 읽기
    size_t bytes_read = fread(private_key, sizeof(char), 4096, pipe);
    private_key[bytes_read] = '\0'; // 문자열 종료

    // 파이프 종료
    if (pclose(pipe) == -1) {
        free(private_key);
        return NULL; // pclose 실패 시 NULL 반환
    }

    return private_key; // 생성된 RSA 비공개 키 반환
}