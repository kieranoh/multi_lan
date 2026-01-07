#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[512];
    struct stat st = {0};

    // 디렉토리가 존재하지 않으면 생성
    if (stat(directory, &st) == -1) {
        mkdir(directory, 0700);
    }

    // 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일을 쓰기 모드로 열기
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 파일에 내용 쓰기
    fprintf(file, "%s", content);
    fclose(file);

    // 파일의 권한을 변경하여 현재 사용자만 접근할 수 있도록 설정
    chmod(filepath, 0600);
}