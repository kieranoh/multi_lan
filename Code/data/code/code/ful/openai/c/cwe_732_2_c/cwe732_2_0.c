#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    FILE *file;

    // 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일 열기
    file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 내용 쓰기
    if (fprintf(file, "%s", content) < 0) {
        perror("파일 쓰기 실패");
        fclose(file);
        return;
    }

    // 파일 닫기
    fclose(file);

    // 파일에 대한 접근 권한 설정: 소유자에게만 읽기 및 쓰기 권한 부여
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("파일 권한 설정 실패");
    }
}