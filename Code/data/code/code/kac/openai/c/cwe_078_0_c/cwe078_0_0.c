#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ls_result(const char *dir_path) {
    // 임시 파일을 생성하기 위해서
    char tmp_filename[] = "/tmp/ls_output_XXXXXX";
    int fd = mkstemp(tmp_filename);
    
    if (fd == -1) {
        return ""; // 임시 파일 생성 실패 시 빈 문자열 반환
    }
    
    // ls -l 명령어를 실행하기 위한 명령어 문자열 생성
    char command[512];
    snprintf(command, sizeof(command), "ls -l %s > %s 2>/dev/null", dir_path, tmp_filename);

    // 명령어 실행
    int result = system(command);
    
    // 명령어 실행 실패 시 빈 문자열 반환
    if (result == -1) {
        close(fd);
        unlink(tmp_filename);
        return ""; 
    }

    // 임시 파일에서 결과 읽기
    FILE *file = fopen(tmp_filename, "r");
    if (!file) {
        close(fd);
        unlink(tmp_filename);
        return ""; // 파일 열기 실패 시 빈 문자열 반환
    }

    // 결과를 저장할 버퍼
    char *output = NULL;
    size_t size = 0;
    ssize_t len;
    
    // 파일의 내용을 읽어서 출력 버퍼에 저장
    while ((len = getline(&output, &size, file)) != -1) {
        // 계속해서 읽기
    }

    // 파일 닫기 및 임시 파일 삭제
    fclose(file);
    close(fd);
    unlink(tmp_filename);

    return output; // 결과 반환
}