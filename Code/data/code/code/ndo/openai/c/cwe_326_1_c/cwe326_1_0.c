#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 실행합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return NULL; // Error creating temp file
    }
    close(fd);

    // DSA parameters generation command
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command_param) == NULL) {
        unlink(param_filename); // Clean up temp file
        return NULL; // Error generating parameters
    }

    // DSA key generation command
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out %s %s", "/tmp/dsa_private_key.pem", param_filename);
    if (execute_command(command_key) == NULL) {
        unlink(param_filename); // Clean up temp file
        return NULL; // Error generating key
    }

    // Read the generated private key
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // Clean up temp file
        return NULL; // Error opening key file
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    rewind(key_file);
    
    char* key = malloc(key_length + 1);
    if (key == NULL) {
        fclose(key_file);
        unlink(param_filename); // Clean up temp file
        return NULL; // Memory allocation error
    }
    
    fread(key, 1, key_length, key_file);
    key[key_length] = '\0'; // Null-terminate the string
    fclose(key_file);
    
    unlink(param_filename); // Clean up temp file
    unlink("/tmp/dsa_private_key.pem"); // Clean up generated key file

    return key; // Return the DSA private key
}