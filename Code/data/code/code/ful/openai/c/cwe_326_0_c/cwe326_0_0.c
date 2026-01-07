#include <stdio.h>
#include <stdlib.h>

char *create_private_key() {
    // 명령어를 실행하기 위한 버퍼
    FILE *fp;
    char *result = NULL;
    char buffer[1024];
    size_t result_size = 0;

    // openssl 명령어를 구성
    const char *command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";

    // 명령어 실행
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류가 발생한 경우 NULL 반환
    }

    // 결과를 읽어서 동적으로 메모리에 저장
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        char *new_result = realloc(result, result_size + len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(fp);
            return NULL; // 메모리 할당 실패 시 NULL 반환
        }
        result = new_result;
        strcpy(result + result_size, buffer);
        result_size += len;
    }

    // 프로세스 종료
    if (pclose(fp) == -1) {
        free(result);
        return NULL; // pclose 실패 시 NULL 반환
    }

    return result; // PEM 형식의 생성된 RSA 비공개 키 반환
}