#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // 명령어를 담을 버퍼 크기 설정
    const int key_length = 2048; // 키 길이 설정
    char command[256];
    sprintf(command, "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // 파이프를 통해 명령 실행
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류 발생 시 NULL 반환
    }

    // 결과를 저장할 버퍼 할당
    char *private_key = NULL;
    size_t size = 0;

    // 반환된 키를 읽어들임
    // 초기 메모리 할당
    private_key = malloc(4096); // 충분한 크기로 메모리 할당
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    
    // 키를 파일에서 읽어옴
    while (fgets(private_key + size, 4096 - size, fp) != NULL) {
        size += strlen(private_key + size);
        if (size >= 4096) break; // 버퍼 오버플로 방지
    }

    pclose(fp);
    return private_key; // 생성된 키 반환
}