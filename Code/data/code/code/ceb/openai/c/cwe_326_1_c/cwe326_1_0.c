#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고, PEM 형식으로 내보내며, 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 실행합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return 생성된 DSA 개인 키를 PEM 형식으로 반환하거나, 오류가 발생한 경우 NULL을 반환합니다. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // Temp file for DSA parameters
    int fd = mkstemp(param_filename); // Create a unique temporary file
    if (fd == -1) {
        return NULL; // Failed to create temporary file
    }
    close(fd); // Close the file descriptor

    // Generate DSA parameters
    char command[256];
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    if (execute_command(command) == NULL) {
        unlink(param_filename); // Cleanup temp file if command fails
        return NULL;
    }

    // Generate DSA private key
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", param_filename, param_filename);
    char* dsa_key = execute_command(command);
    
    // Cleanup the temporary file
    unlink(param_filename);
    
    return dsa_key; // Return the generated DSA private key or NULL if there was an error
}