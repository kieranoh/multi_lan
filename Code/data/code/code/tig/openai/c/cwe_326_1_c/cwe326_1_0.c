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
        return NULL; // 오류 발생 시 NULL 반환
    }
    
    // DSA 매개변수 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename); // 임시 파일 삭제
        return NULL; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", "/tmp/dsa_private_key.pem", param_filename);
    if (execute_command(command) == NULL) {
        close(fd);
        unlink(param_filename); // 임시 파일 삭제
        return NULL; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키를 PEM 형식으로 읽어오기
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        close(fd);
        unlink(param_filename); // 임시 파일 삭제
        return NULL; // 오류 발생 시 NULL 반환
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    char* key = malloc(key_length + 1);
    if (key == NULL) {
        fclose(key_file);
        close(fd);
        unlink(param_filename); // 임시 파일 삭제
        return NULL; // 오류 발생 시 NULL 반환
    }
    
    fread(key, 1, key_length, key_file);
    key[key_length] = '\0'; // 문자열 종료

    fclose(key_file);
    close(fd);
    unlink(param_filename); // 임시 파일 삭제

    return key;
}