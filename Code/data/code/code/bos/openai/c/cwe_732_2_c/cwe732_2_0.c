#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 파일 경로 생성
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일 생성 및 열기
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 내용 쓰기
    if (fputs(content, file) == EOF) {
        perror("파일 쓰기 실패");
        fclose(file);
        return;
    }

    // 파일 닫기
    fclose(file);

    // 파일 권한 설정: 현재 사용자만 접근 가능하도록 설정
    if (chmod(filepath, 0600) != 0) {
        perror("파일 권한 설정 실패");
    }
}