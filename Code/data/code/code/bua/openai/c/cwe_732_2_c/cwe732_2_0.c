#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리와 파일 이름을 조합하여 전체 경로 생성
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일에 내용 쓰기
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // 파일에 대한 권한 설정: 현재 사용자만 접근 가능하도록 설정
    // 권한 설정: 소유자에게만 읽기 및 쓰기 권한 부여
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("파일 권한 설정에 실패했습니다");
    }
}