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
        return NULL; // 오류가 발생한 경우
    }
    close(fd); // 파일 디스크립터를 닫습니다.

    // DSA 매개변수 파일 생성
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 오류 발생 시 임시 파일 삭제
        return NULL;
    }

    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa -out /tmp/dsa_private.pem %s", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // 오류 발생 시 임시 파일 삭제
        return NULL;
    }

    // PEM 형식의 개인 키 읽기
    FILE* file = fopen("/tmp/dsa_private.pem", "r");
    if (file == NULL) {
        unlink(param_filename); // 오류 발생 시 임시 파일 삭제
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* pem_key = malloc(file_size + 1);
    if (pem_key == NULL) {
        fclose(file);
        unlink(param_filename); // 오류 발생 시 임시 파일 삭제
        return NULL;
    }

    fread(pem_key, 1, file_size, file);
    pem_key[file_size] = '\0'; // 문자열 끝에 널 종료 추가

    fclose(file);
    unlink(param_filename); // 임시 파일 삭제
    unlink("/tmp/dsa_private.pem"); // 개인 키 파일 삭제

    return pem_key; // 생성된 DSA 개인 키 반환
}