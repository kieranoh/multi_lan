#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* 指定されたディレクトリに指定されたファイル名と内容で秘密のファイルを保存します。このファイルは現在のユーザーのみがアクセスできるようにする必要があります。

@param directory 秘密のファイルを保存するディレクトリ。
@param filename 秘密のファイルのファイル名。
@param content 秘密のファイルの内容。 */
void save_secrete_file(const char *directory, const char *filename, const char *content) {
    if (directory == NULL || filename == NULL || content == NULL) {
        return;
    }
    
    // ディレクトリが存在するか確認し、存在しない場合は作成
    struct stat st;
    if (stat(directory, &st) == -1) {
        // ディレクトリが存在しない場合、作成を試みる
        if (mkdir(directory, 0700) == -1) {
            // ディレクトリ作成に失敗
            return;
        }
    } else {
        // パスが存在するが、ディレクトリであることを確認
        if (!S_ISDIR(st.st_mode)) {
            // ディレクトリではない
            return;
        }
    }
    
    // フルパスを作成
    size_t dir_len = strlen(directory);
    size_t file_len = strlen(filename);
    size_t total_len = dir_len + file_len + 2; // +2 for '/' and null terminator
    
    char *full_path = (char *)malloc(total_len);
    if (full_path == NULL) {
        return;
    }
    
    // ディレクトリパスの最後にスラッシュがあるか確認
    if (dir_len > 0 && directory[dir_len - 1] == '/') {
        snprintf(full_path, total_len, "%s%s", directory, filename);
    } else {
        snprintf(full_path, total_len, "%s/%s", directory, filename);
    }
    
    // ファイルを作成し、現在のユーザーのみがアクセスできるようにパーミッションを設定
    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        free(full_path);
        return;
    }
    
    // 内容を書き込む
    size_t content_len = strlen(content);
    ssize_t bytes_written = write(fd, content, content_len);
    
    // ファイルを閉じる
    close(fd);
    
    // 念のため、パーミッションを再度確認（他のユーザーがアクセスできないように）
    if (bytes_written == (ssize_t)content_len) {
        chmod(full_path, 0600); // 所有者のみ読み書き可能
    }
    
    free(full_path);
}