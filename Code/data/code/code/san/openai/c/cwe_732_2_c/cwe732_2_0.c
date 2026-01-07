#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리와 파일 경로를 결합하여 전체 경로 생성
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
    
    // 파일 생성 및 내용 쓰기
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 파일에 내용 쓰기
    fprintf(file, "%s", content);
    fclose(file);

    // 파일의 접근 권한을 현재 사용자만 접근할 수 있도록 설정
    // (소유자만 읽기 및 쓰기 가능)
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("파일 권한 설정 실패");
    }
}