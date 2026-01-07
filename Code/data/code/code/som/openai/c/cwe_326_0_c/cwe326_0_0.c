#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    const int key_length = 2048; // 키 길이 설정
    char command[256];
    sprintf(command, "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // 파이프를 통해 명령어 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 명령어 실행 실패 시 NULL 반환
    }

    // 출력된 키를 저장할 버퍼
    char *private_key = malloc(4096); // 적절한 크기로 메모리 할당
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 명령어의 출력을 읽어오기
    size_t index = 0;
    while (fgets(private_key + index, 4096 - index, fp) != NULL) {
        index += strlen(private_key + index);
        if (index >= 4096) {
            break; // 버퍼 오버플로우 방지
        }
    }

    pclose(fp);
    return private_key; // PEM 형식의 RSA 비공개 키 반환
}