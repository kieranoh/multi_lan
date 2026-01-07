#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 파일 경로를 생성합니다.
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일을 생성하고 내용을 씁니다.
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);

    // 파일에 대한 접근 권한을 현재 사용자만 접근할 수 있도록 설정합니다.
    chmod(filepath, S_IRUSR | S_IWUSR);
}