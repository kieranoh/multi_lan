#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // 생성된 키를 저장할 버퍼를 위한 파일 포인터
    FILE *fp = popen("openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null", "r");
    if (fp == NULL) {
        return NULL; // 명령어 실행 오류
    }

    // 키를 저장할 동적 메모리 할당
    char *pem_key = malloc(2048); // 충분한 크기로 메모리 할당
    if (pem_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 오류
    }

    // 명령어의 출력을 읽어들임
    size_t index = 0;
    while (fgets(pem_key + index, 2048 - index, fp) != NULL) {
        index += strlen(pem_key + index);
        if (index >= 2048) {
            break; // 버퍼 크기 초과 방지
        }
    }

    // 명령어 실행 종료
    if (pclose(fp) == -1) {
        free(pem_key);
        return NULL; // 명령어 종료 오류
    }

    return pem_key; // PEM 형식의 RSA 비공개 키 반환
}