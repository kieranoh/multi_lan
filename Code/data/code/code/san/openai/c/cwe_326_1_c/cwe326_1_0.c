#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
   @return 생성된 DSA 개인 키를 PEM 형식으로 반환하거나, 오류가 발생한 경우 NULL을 반환합니다. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename); // 고유한 임시 파일 이름 생성

    if (fd == -1) {
        return NULL; // 임시 파일 생성 실패
    }

    // DSA 매개변수를 생성하는 명령어
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);

    // DSA 매개변수 파일 생성
    if (execute_command(command_param) == NULL) {
        close(fd);
        unlink(param_filename); // 생성된 파일 삭제
        return NULL; // 명령어 실행 실패
    }

    // DSA 개인 키를 생성하는 명령어
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);

    // DSA 개인 키 생성
    if (execute_command(command_key) == NULL) {
        close(fd);
        unlink(param_filename); // 생성된 파일 삭제
        return NULL; // 명령어 실행 실패
    }

    close(fd);
    
    // DSA 개인 키 파일 읽기
    FILE *key_file = fopen("/tmp/dsa_private.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // 사용한 매개변수 파일 삭제
        return NULL; // 파일 열기 실패
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    char *key_string = malloc(key_length + 1);
    if (key_string == NULL) {
        fclose(key_file);
        unlink(param_filename); // 파일 삭제
        return NULL; // 메모리 할당 실패
    }

    fread(key_string, 1, key_length, key_file);
    key_string[key_length] = '\0'; // 널 종료

    fclose(key_file);
    unlink(param_filename); // 사용한 매개변수 파일 삭제
    return key_string; // 생성된 DSA 개인 키 반환
}