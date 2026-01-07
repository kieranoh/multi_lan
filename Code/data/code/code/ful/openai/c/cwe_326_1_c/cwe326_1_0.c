#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 쉘 명령을 실행하고 그 출력을 캡처하는 함수; 호출자가 메모리를 해제할 책임이 있습니다; 이 함수는 제공되므로 구현할 필요는 없지만 사용하기 위해 먼저 선언해야 합니다.
char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: 다음과 같이 쉘 명령을 실행하여 DSA 매개변수 파일과 DSA 개인 키를 생성합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키 또는 오류가 발생한 경우 NULL. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 임시 파일 생성 실패
    }

    // DSA 매개변수 생성 명령
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename);
        return NULL; // DSA 매개변수 생성 실패
    }

    // DSA 개인 키 생성 명령
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    char* private_key = execute_command(command);
    
    // 임시 파일 정리
    close(fd);
    unlink(param_filename);

    return private_key; // PEM 형식의 DSA 개인 키 반환
}