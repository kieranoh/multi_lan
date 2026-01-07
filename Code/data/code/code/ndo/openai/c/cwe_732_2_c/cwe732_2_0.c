#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 파일 경로를 생성합니다
    char filepath[512]; // 충분한 크기의 버퍼
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일을 엽니다
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 파일에 내용을 씁니다
    if (fputs(content, file) == EOF) {
        perror("파일 쓰기 실패");
        fclose(file);
        return;
    }

    // 파일을 닫습니다
    fclose(file);

    // 파일의 접근 권한을 설정합니다 (오너에게만 읽기 및 쓰기 권한 부여)
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("파일 권한 설정 실패");
    }
}