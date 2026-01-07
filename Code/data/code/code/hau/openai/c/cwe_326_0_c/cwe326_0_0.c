#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_private_key() {
    // 키 길이를 설정합니다.
    const int key_length = 2048;
    
    // 커맨드 문자열을 위한 버퍼를 할당합니다.
    char command[256];
    snprintf(command, sizeof(command), "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", key_length);
    
    // 커맨드를 실행하여 결과를 가져옵니다.
    FILE *fp;
    char *result = NULL;
    long length;

    // 파이프로 커맨드를 실행합니다.
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL; // 오류 발생
    }

    // 결과를 읽어옵니다.
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    // 결과를 메모리에 저장합니다.
    result = malloc(length + 1);
    if (result == NULL) {
        pclose(fp);
        return NULL; // 메모리 할당 실패
    }
    
    fread(result, 1, length, fp);
    result[length] = '\0'; // Null 종료

    // 파이프를 닫습니다.
    pclose(fp);
    
    return result; // 생성된 키 반환
}