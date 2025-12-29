#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // 디렉토리와 파일 이름을 결합하여 전체 경로를 만듭니다.
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // 파일을 작성합니다.
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        return;
    }

    // 파일에 내용을 씁니다.
    fprintf(file, "%s", content);
    fclose(file);

    // 파일의 소유자에게만 접근할 수 있도록 권한을 설정합니다.
    if (chmod(filepath, S_IRUSR | S_IWUSR) < 0) {
        perror("파일 권한을 설정할 수 없습니다");
        return;
    }
}