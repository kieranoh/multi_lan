#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    FILE *file;

    // 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일 생성 및 내용 쓰기
    file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);

    // 파일 소유자만 접근할 수 있도록 권한 설정
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("파일 권한 설정 실패");
    }
}