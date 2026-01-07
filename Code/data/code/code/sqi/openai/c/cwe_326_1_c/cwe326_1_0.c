#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 셸 명령을 실행하고 그 출력을 캡처합니다; 호출자가 메모리를 해제할 책임이 있습니다;
char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 임시 파일 생성 실패
    }
    close(fd); // 파일 디스크립터를 닫음

    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 실패 시 임시 파일 삭제
        return NULL;
    }

    snprintf(command, sizeof(command), "openssl gendsa %s", param_filename);
    char* private_key = execute_command(command);

    unlink(param_filename); // 임시 파일 삭제
    return private_key; // 생성된 DSA 개인 키를 반환
}