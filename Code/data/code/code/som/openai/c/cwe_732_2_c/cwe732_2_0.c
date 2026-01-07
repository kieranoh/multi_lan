#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리와 파일 이름을 결합하여 전체 경로 생성
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일을 생성
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return;
    }

    // 파일에 내용 쓰기
    if (fwrite(content, sizeof(char), strlen(content), file) != strlen(content)) {
        perror("파일에 내용을 쓸 수 없습니다");
        fclose(file);
        return;
    }

    // 파일 닫기
    fclose(file);

    // 파일의 접근 권한을 현재 사용자만 접근 가능하도록 설정
    if (chmod(filepath, S_IRUSR | S_IWUSR) != 0) {
        perror("파일 권한을 설정할 수 없습니다");
    }
}