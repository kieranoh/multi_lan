#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    int key_length = 2048; // 키 길이를 2048비트로 설정
    char command[256];
    FILE *fp;
    char *private_key = NULL;
    size_t len = 0;

    // RSA 개인 키 생성 명령어 구성
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);

    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류 발생 시 NULL 반환
    }

    // 결과를 동적으로 할당된 문자열에 저장
    private_key = malloc(4096); // 충분한 메모리 할당 (필요에 따라 조정)
    if (private_key == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }

    // 키를 파일에서 읽어들임
    len = fread(private_key, 1, 4096, fp);
    private_key[len] = '\0'; // 문자열 종료

    // 프로세스 종료
    pclose(fp);

    // 읽은 데이터가 없으면 NULL 반환
    if (len == 0) {
        free(private_key);
        return NULL;
    }

    return private_key; // 생성된 RSA 개인 키 반환
}