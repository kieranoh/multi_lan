#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // 오류 발생
    }
    
    // DSA 키 길이 설정 (예: 2048)
    const int key_length = 2048;
    char command[256];

    // DSA 파라미터 생성 명령
    snprintf(command, sizeof(command), "openssl dsaparam -out %s %d", param_filename, key_length);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename); // 오류 시 임시 파일 삭제
        return NULL;
    }

    // DSA 개인 키 생성 명령
    snprintf(command, sizeof(command), "openssl gendsa -out /dev/stdout %s", param_filename);
    char* private_key = execute_command(command);
    
    // 임시 파일 삭제
    unlink(param_filename);
    close(fd);
    
    return private_key; // 생성된 DSA 개인 키 반환
}