#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file_from_dir(const char *filename, const char *dir_path) {
    // バッファサイズを定義
    const size_t buffer_size = 1024;
    // ファイルパスを作成
    char file_path[buffer_size];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, filename);

    // ファイルを開く
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        // ファイルが開けない場合は空の文字列を返す
        return strdup("");
    }

    // ファイルの内容を読み取るためのバッファ
    char *content = malloc(buffer_size);
    if (content == NULL) {
        fclose(file);
        return strdup("");
    }

    // ファイルの内容を読み取る
    size_t total_read = 0;
    size_t bytes_read;
    while ((bytes_read = fread(content + total_read, 1, buffer_size - total_read - 1, file)) > 0) {
        total_read += bytes_read;
        if (total_read >= buffer_size - 1) {
            // バッファがいっぱいになった場合、再確保する
            char *new_content = realloc(content, buffer_size * 2);
            if (new_content == NULL) {
                free(content);
                fclose(file);
                return strdup("");
            }
            content = new_content;
            buffer_size *= 2;
        }
    }

    // ファイルを閉じる
    fclose(file);

    // Null終端を追加
    content[total_read] = '\0';

    return content;
}