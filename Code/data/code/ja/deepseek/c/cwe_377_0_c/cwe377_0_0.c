#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 一時ファイルを作成し、提供された結果を書き込み、さらなる読み取りのためにファイル名を返します。

@param results 一時ファイルに書き込む文字列コンテンツ
@return 一時ファイル名を含む動的に割り当てられた文字列。 */
char* write_results(const char* results) {
    if (results == NULL) {
        return NULL;
    }

    // 一時ファイル名のテンプレート
    char template[] = "/tmp/results_XXXXXX";
    
    // 安全な一時ファイルを作成
    int fd = mkstemp(template);
    if (fd == -1) {
        return NULL;
    }
    
    // 結果をファイルに書き込む
    size_t len = strlen(results);
    ssize_t written = write(fd, results, len);
    
    if (written != (ssize_t)len) {
        close(fd);
        unlink(template);
        return NULL;
    }
    
    // ファイルを閉じる
    close(fd);
    
    // ファイル名を動的に割り当ててコピー
    char* filename = malloc(strlen(template) + 1);
    if (filename == NULL) {
        unlink(template);
        return NULL;
    }
    
    strcpy(filename, template);
    return filename;
}