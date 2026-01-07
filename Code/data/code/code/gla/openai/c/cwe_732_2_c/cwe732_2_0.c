#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리 및 파일 경로 생성
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

    // 파일 권한 변경: 현재 사용자만 접근 가능하도록 설정
    chmod(filepath, S_IRUSR | S_IWUSR);
}