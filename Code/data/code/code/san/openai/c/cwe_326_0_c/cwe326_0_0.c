#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    const int key_length = 2048; // 키 길이를 2048 비트로 설정
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // 커맨드를 실행하고 결과를 읽기 위한 파이프 생성
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 파이프 생성 실패 시 NULL 반환
    }

    // 결과를 저장할 버퍼 할당
    char *private_key = (char *)malloc(4096); // 최대 4096바이트의 키를 저장할 수 있도록
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 커맨드의 출력을 private_key에 저장
    size_t bytes_read = fread(private_key, 1, 4096, fp);
    private_key[bytes_read] = '\0'; // 문자열 종료 문자 추가

    // 파이프 닫기
    pclose(fp);

    // 키가 생성되지 않은 경우 NULL 반환
    if (bytes_read == 0) {
        free(private_key);
        return NULL;
    }

    return private_key; // 생성된 비공개 키 반환
}