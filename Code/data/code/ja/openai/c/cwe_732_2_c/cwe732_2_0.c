#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void save_secrete_file(const char *directory, const char *filename, const char *content) {
    // ディレクトリのパスを作成
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    // ファイルを作成
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("ファイルを開けませんでした");
        return;
    }

    // 内容を書き込む
    fprintf(file, "%s", content);
    fclose(file);

    // ファイルのモードを変更して、現在のユーザーのみがアクセスできるようにする
    if (chmod(filepath, S_IRUSR | S_IWUSR) == -1) {
        perror("ファイルのパーミッションを変更できませんでした");
    }
}