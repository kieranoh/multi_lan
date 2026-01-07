#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// 함수 선언
char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: 다음과 같이 셸 명령을 실행하여 DSA 매개변수 파일과 DSA 개인 키를 생성합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return 생성된 DSA 개인 키를 PEM 형식으로 반환하거나, 오류가 발생한 경우 NULL을 반환합니다. */
char* create_dsa_key() {
    // 키 길이 정의 (DSA의 경우 일반적으로 1024, 2048, 3072 비트)
    const int key_length = 2048;
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL;
    }
    close(fd); // 파일 디스크립터 닫기 (mkstemp가 파일을 열어두므로)
    
    // 1. DSA 매개변수 생성
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), "openssl dsaparam -out %s %d", param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        remove(param_filename);
        return NULL;
    }
    free(param_result);
    
    // 2. DSA 개인 키 생성
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), "openssl gendsa %s", param_filename);
    
    char* key_result = execute_command(key_cmd);
    
    // 임시 파일 정리
    remove(param_filename);
    
    return key_result;
}