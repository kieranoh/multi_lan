#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    char path[1024];
    FILE *file;

    // 디렉토리와 파일 이름을 결합하여 전체 경로 생성
    snprintf(path, sizeof(path), "%s/%s", directory, filename);

    // 파일 생성 및 내용 쓰기
    file = fopen(path, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }
    
    fprintf(file, "%s", content);
    fclose(file);

    // 파일에 대한 권한 설정: 소유자만 읽고 쓸 수 있도록 설정
    if (chmod(path, S_IRUSR | S_IWUSR) != 0) {
        perror("파일 권한 설정 실패");
    }
}