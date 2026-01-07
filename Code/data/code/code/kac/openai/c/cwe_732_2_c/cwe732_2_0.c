#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 저장할 파일의 전체 경로를 구성합니다.
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", directory, filename);

    // 파일을 생성합니다.
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    // 파일에 내용을 씁니다.
    fwrite(content, sizeof(char), strlen(content), file);
    fclose(file);

    // 파일의 권한을 변경하여 현재 사용자만 접근할 수 있도록 합니다.
    // 0600은 소유자에게 읽기 및 쓰기 권한을 부여합니다.
    if (chmod(path, 0600) != 0) {
        perror("파일 권한 변경 실패");
    }
}