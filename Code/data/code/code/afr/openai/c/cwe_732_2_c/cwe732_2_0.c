#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char filepath[1024];
    FILE *file;

    // 디렉토리와 파일 이름을 결합하여 전체 파일 경로 생성
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일 생성 및 내용 쓰기
    file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // 파일 권한을 현재 사용자만 접근할 수 있도록 설정
    // 파일의 권한을 600으로 설정
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("파일 권한 설정 실패");
    }
}